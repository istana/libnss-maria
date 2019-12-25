#include "./group.h"

enum nss_status _nss_maria_setgrent (void) {
  maria_log("_nss_maria_setgrent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_endgrent (void) {
  maria_log("_nss_maria_endgrent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getgrent_r (
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getgrent_r called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getgrnam_r (
  const char *name,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrnam_r called!");

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
    "_nss_maria_getgrnam_r",
    settings->getgrnam,
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

  enum nss_status result_status = copy_db_row_to_group(row, group_result, buffer, buflen, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return result_status;
}

enum nss_status _nss_maria_getgrgid_r (
  uid_t gid,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrgid_r called!");

  Maria_config *settings = malloc(sizeof(*settings));
  maria_read_config_file(settings, "/etc/libnss-maria.conf");
  debug_print_var("_nss_maria_getgrgid_r database settings-dbhost:%s;dbname:%s;\
dbuser:%s;dbpass:%s;dbport:%lld;getpwnam_query:%s",
    settings->dbhost,
    settings->dbname,
    settings->dbuser,
    settings->dbpass,
    settings->dbport,
    settings->getpwnam
  );

  // TODO: should return error when longer than entered
  char gid_as_string[256];
  snprintf(gid_as_string, 255, "%d", gid);

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getgrgid_r",
    settings->getgrgid,
    gid_as_string,
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

  enum nss_status result_status = copy_db_row_to_group(row, group_result, buffer, buflen, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return result_status;
}
