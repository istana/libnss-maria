#include "./shadow.h"

thread_local MYSQL *shadow_dbconn = NULL;
thread_local MYSQL_RES *shadow_dbresult = NULL;

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
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;

  READ_USER_CONFIG(errnop);

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getspnam_r",
    settings->getspnam,
    name,
    settings,
    &conn,
    &result,
    errnop,
    1
  );

  if (status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return status;
  }

  enum nss_status row_status = maria_get_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_shadow(row, shadow_result, buffer, buflen, errnop);

  CLEANUP();
  return result_status;
}

enum nss_status _nss_maria_getspent_r (
  struct spwd *shadow_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getspent_r called!");

  MYSQL_ROW row;
  enum nss_status row_status = maria_get_row(&shadow_dbconn, &shadow_dbresult, &row, errnop);
  if (row_status != NSS_STATUS_SUCCESS) {
    return row_status;
  }

  return copy_db_row_to_shadow(row, shadow_result, buffer, buflen, errnop);
}
enum nss_status _nss_maria_setspent (void) {
  debug_print("_nss_maria_setspent called!");

  int err;
  Maria_config *settings = malloc(sizeof(*settings));
  READ_USER_CONFIG(&err);

  enum nss_status status = maria_query_no_param(
    "_nss_maria_setspent",
    settings->getspent,
    settings,
    &shadow_dbconn,
    &shadow_dbresult,
    &err,
    1
  );

  free(settings);
  return status;
}

enum nss_status _nss_maria_endspent (void) {
  debug_print("_nss_maria_endspent called!");

  if(shadow_dbresult != NULL) mysql_free_result(shadow_dbresult);
  if(shadow_dbconn != NULL) mysql_close(shadow_dbconn);
  return NSS_STATUS_SUCCESS;
}
