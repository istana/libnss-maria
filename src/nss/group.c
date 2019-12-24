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
  struct group *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrnam_r called!");
  Maria_config *settings = malloc(sizeof(*settings));
  maria_read_config_file(settings, "/etc/libnss-maria.conf");
  debug_print_var("_nss_maria_getgrnam_r database settings-dbhost:%s;dbname:%s;\
dbuser:%s;dbpass:%s;dbport:%lld;getpwnam_query:%s",
    settings->dbhost,
    settings->dbname,
    settings->dbuser,
    settings->dbpass,
    settings->dbport,
    settings->getpwnam
  );

  const char *placeholder = memchr(settings->getgrnam, '?', strlen(settings->getgrnam));

  if(!placeholder) {
    debug_print("_nss_maria_getgrnam_r placeholder not found in database query");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn = mysql_init(NULL);
  if(!conn) {
    debug_print("mysql init failed, out of memory");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  if(mysql_real_connect(
    conn,
    settings->dbhost,
    settings->dbuser,
    settings->dbpass,
    settings->dbname,
    settings->dbport,
    NULL,
    0
  ) == NULL) {
    debug_print("_nss_maria_getgrnam_r cannot connect to the database");
    free(settings);
    return NSS_STATUS_TRYAGAIN;
  }

  char *name_sanitized = malloc((sizeof(char) * strlen(name) * 2) + 1);
  mysql_real_escape_string(conn, name_sanitized, name, strlen(name));
  char *final_query = str_replace(settings->getgrnam, "?", name_sanitized);
  debug_print_var(final_query);

  if (mysql_real_query(conn, final_query, strlen(final_query)) != 0) {
    debug_print("_nss_maria_getgrnam_r cannot execute getpwnam mariadb query");
    log_mysql_error(conn);
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_RES *result = mysql_store_result(conn);

  if(result == NULL) {
    debug_print("_nss_maria_getgrnam_r cannot get result from query");
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_ROW row = mysql_fetch_row(result);

  if (row == NULL) {
    debug_print("_nss_maria_getgrnam_r no result found");
    free(settings);
    free(name_sanitized);
    free(final_query);
    mysql_free_result(result);
    return NSS_STATUS_NOTFOUND;
  }

  char *xname = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);

  strncpy(xname, row[0], 255);
  strncpy(password, row[1], 255);

  result_buf->gr_name = xname;
  result_buf->gr_passwd = password;
  result_buf->gr_gid = strtoul(row[2], NULL, 10);

  free(settings);
  free(name_sanitized);
  free(final_query);
  mysql_free_result(result);
  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_maria_getgrgid_r (
  uid_t gid,
  struct group *result_buf,
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

  const char *placeholder = memchr(settings->getgrgid, '?', strlen(settings->getgrgid));

  if(!placeholder) {
    debug_print("_nss_maria_getgrgid_r placeholder not found in database query");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn = mysql_init(NULL);
  if(!conn) {
    debug_print("mysql init failed, out of memory");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  if(mysql_real_connect(
    conn,
    settings->dbhost,
    settings->dbuser,
    settings->dbpass,
    settings->dbname,
    settings->dbport,
    NULL,
    0
  ) == NULL) {
    debug_print("_nss_maria_getgrgid_r cannot connect to the database");
    free(settings);
    return NSS_STATUS_TRYAGAIN;
  }


  // TODO: should return error when longer than entered
  char uid_as_string[256];
  snprintf(uid_as_string, 255, "%d", gid);

  char *name_sanitized = malloc((sizeof(char) * strlen(uid_as_string) * 2) + 1);
  mysql_real_escape_string(conn, name_sanitized, uid_as_string, strlen(uid_as_string));
  char *final_query = str_replace(settings->getgrgid, "?", name_sanitized);
  debug_print_var(final_query);

  if (mysql_real_query(conn, final_query, strlen(final_query)) != 0) {
    debug_print("_nss_maria_getgrgid_r cannot execute getpwnam mariadb query");
    log_mysql_error(conn);
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_RES *result = mysql_store_result(conn);

  if(result == NULL) {
    debug_print("_nss_maria_getgrgid_r cannot get result from query");
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_ROW row = mysql_fetch_row(result);

  if (row == NULL) {
    debug_print("_nss_maria_getgrgid_r no result found");
    free(settings);
    free(name_sanitized);
    free(final_query);
    mysql_free_result(result);
    return NSS_STATUS_NOTFOUND;
  }

  char *xname = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);

  strncpy(xname, row[0], 255);
  strncpy(password, row[1], 255);

  result_buf->gr_name = xname;
  result_buf->gr_passwd = password;
  result_buf->gr_gid = strtoul(row[2], NULL, 10);

  free(settings);
  free(name_sanitized);
  free(final_query);
  mysql_free_result(result);
  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_maria_initgroups_dyn (
  const char *user,
  gid_t group,
  long int *start,
  long int *size,
  gid_t **groupsp,
  long int limit,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_initgroups_dyn called!");
  return NSS_STATUS_NOTFOUND;
}
