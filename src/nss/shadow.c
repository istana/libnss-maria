#include "./shadow.h"

enum nss_status _nss_maria_setspent (void) {
  maria_log("_nss_maria_setspent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_endspent (void) {
  maria_log("_nss_maria_endspent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getspent_r (
  struct spwd *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getspent_r called!");
  return NSS_STATUS_NOTFOUND;
}

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
  maria_read_config_file(settings, "/etc/libnss-maria.conf");
  debug_print_var("_nss_maria_getpwnam_r database settings-dbhost:%s;dbname:%s;\
dbuser:%s;dbpass:%s;dbport:%lld;getpwnam_query:%s",
    settings->dbhost,
    settings->dbname,
    settings->dbuser,
    settings->dbpass,
    settings->dbport,
    settings->getpwnam
  );
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
