#include "./passwd.h"

thread_local MYSQL *passwd_dbconn = NULL;
thread_local MYSQL_RES *passwd_dbresult = NULL;

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
  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW_OFFSET result_initial_offset;
  MYSQL_ROW row;

  READ_USER_CONFIG(errnop);

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getpwnam_r",
    settings->getpwnam,
    name,
    settings,
    &conn,
    &result,
    errnop,
    0
  );

  if (status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return status;
  }

  result_initial_offset = mysql_row_tell(result);
  enum nss_status row_status = maria_get_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_passwd(result, result_initial_offset, row, passwd_result, buffer, buflen, errnop);

  CLEANUP();
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
  READ_USER_CONFIG(errnop);

  if (sizeof(uid) > 16) {
    maria_log("uid size is too high (more than 16 bytes)");
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  char uid_as_string[17];
  snprintf(uid_as_string, 17, "%d", uid);

  MYSQL *conn = NULL;
  MYSQL_RES *result = NULL;
  MYSQL_ROW_OFFSET result_initial_offset;
  MYSQL_ROW row;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getpwuid_r",
    settings->getpwuid,
    uid_as_string,
    settings,
    &conn,
    &result,
    errnop,
    0
  );

  if (status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return status;
  }

  result_initial_offset = mysql_row_tell(result);
  enum nss_status row_status = maria_get_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    CLEANUP();
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_passwd(result, result_initial_offset, row, passwd_result, buffer, buflen, errnop);

  CLEANUP();
  return result_status;
}

enum nss_status _nss_maria_getpwent_r (
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop
) {
  debug_print("_nss_maria_getpwent called!");

  MYSQL_ROW row;
  MYSQL_ROW_OFFSET passwd_db_initial_offset = mysql_row_tell(passwd_dbresult);
  enum nss_status row_status = maria_get_row(&passwd_dbconn, &passwd_dbresult, &row, errnop);
  if (row_status != NSS_STATUS_SUCCESS) {
    return row_status;
  }

  return copy_db_row_to_passwd(passwd_dbresult, passwd_db_initial_offset, row, passwd_result, buffer, buflen, errnop);
}

enum nss_status _nss_maria_setpwent (void) {
  debug_print("_nss_maria_setpwent called!");

  int err;
  Maria_config *settings = malloc(sizeof(*settings));
  READ_USER_CONFIG(&err);

  enum nss_status status = maria_query_no_param(
    "_nss_maria_setpwent",
    settings->getpwent,
    settings,
    &passwd_dbconn,
    &passwd_dbresult,
    &err,
    0
  );

  free(settings);
  return status;
}

enum nss_status _nss_maria_endpwent (void) {
  debug_print("_nss_maria_endpwent called!");

  if(passwd_dbresult != NULL) mysql_free_result(passwd_dbresult);
  if(passwd_dbconn != NULL) mysql_close(passwd_dbconn);
  return NSS_STATUS_SUCCESS;
}
