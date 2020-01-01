#include "./shadow.h"

thread_local MYSQL *shadow_dbconn;
thread_local MYSQL_RES *shadow_dbresult;

enum nss_status _nss_maria_getspnam_r(
  const char *name,
  struct spwd *shadow_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getspnam_r called!");

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getspnam_r",
    settings->getspnam,
    name,
    settings,
    &conn,
    &result,
    errnop
  );

  if (status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return status;
  }

  enum nss_status row_status = maria_get_first_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_shadow(row, shadow_result, buffer, buflen, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return result_status;
}

enum nss_status _nss_maria_getspent_r (
  struct spwd *shadow_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getspent_r called!");

  MYSQL_ROW row;
  enum nss_status row_status = maria_get_first_row(&shadow_dbconn, &shadow_dbresult, &row, errnop);
  if (row_status != NSS_STATUS_SUCCESS) {
    return row_status;
  }

  return copy_db_row_to_shadow(row, shadow_result, buffer, buflen, errnop);
}
enum nss_status _nss_maria_setspent (void) {
  maria_log("_nss_maria_setspent called!");

  int err;
  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  enum nss_status status = maria_query_no_param(
    "_nss_maria_setspent",
    settings->getspent,
    settings,
    &shadow_dbconn,
    &shadow_dbresult,
    &err
  );

  free(settings);
  return status;
}

enum nss_status _nss_maria_endspent (void) {
  maria_log("_nss_maria_endspent called!");

  mysql_free_result(shadow_dbresult);
  mysql_close(shadow_dbconn);
  return NSS_STATUS_SUCCESS;
}
