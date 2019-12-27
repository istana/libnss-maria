#include "./passwd.h"

thread_local MYSQL *passwd_dbconn;
thread_local MYSQL_RES *passwd_dbresult;

enum nss_status _nss_maria_getpwnam_r (
  const char *name,
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getpwnam_r called!");

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
    "_nss_maria_getpwnam_r",
    settings->getpwnam,
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

  enum nss_status result_status = copy_db_row_to_passwd(row, passwd_result, buffer, buflen, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return result_status;
}

enum nss_status _nss_maria_getpwuid_r (
  uid_t uid,
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getpwuid_r called!");

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  // TODO: should return error when longer than entered
  char uid_as_string[256];
  snprintf(uid_as_string, 255, "%d", uid);

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getpwuid_r",
    settings->getpwuid,
    uid_as_string,
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

  enum nss_status result_status = copy_db_row_to_passwd(row, passwd_result, buffer, buflen, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return result_status;
}

enum nss_status _nss_maria_getpwent_r (
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop
) {
  MYSQL_ROW row;
  enum nss_status row_status = maria_get_first_row(&passwd_dbconn, &passwd_dbresult, &row, errnop);
  if (row_status != NSS_STATUS_SUCCESS) {
    return row_status;
  }

  return copy_db_row_to_passwd(row, passwd_result, buffer, buflen, errnop);
}

enum nss_status _nss_maria_setpwent (void) {
  int err;
  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  enum nss_status status = maria_query_no_param(
    "_nss_maria_setpwent",
    settings->getpwent,
    settings,
    &passwd_dbconn,
    &passwd_dbresult,
    &err
  );

  free(settings);
  return status;
}

enum nss_status _nss_maria_endpwent (void) {
  mysql_free_result(passwd_dbresult);
  mysql_close(passwd_dbconn);
  return NSS_STATUS_SUCCESS;
}
