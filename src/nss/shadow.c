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
  struct spwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getspnam_r called!");
  Maria_config *settings = malloc(sizeof(*settings));
  maria_read_config_file(settings, "/etc/libnss-maria.conf");
  debug_print_var("_nss_maria_getspnam_r database settings-dbhost:%s;dbname:%s;\
dbuser:%s;dbpass:%s;dbport:%lld;getpwnam_query:%s",
    settings->dbhost,
    settings->dbname,
    settings->dbuser,
    settings->dbpass,
    settings->dbport,
    settings->getpwnam
  );

  const char *placeholder = memchr(settings->getspnam, '?', strlen(settings->getspnam));

  if(!placeholder) {
    debug_print("_nss_maria_getspnam_r placeholder not found in database query");
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
    debug_print("_nss_maria_getspnam_r cannot connect to the database");
    free(settings);
    return NSS_STATUS_TRYAGAIN;
  }

  char *name_sanitized = malloc((sizeof(char) * strlen(name) * 2) + 1);
  mysql_real_escape_string(conn, name_sanitized, name, strlen(name));
  char *final_query = str_replace(settings->getspnam, "?", name_sanitized);
  debug_print_var(final_query);

  if (mysql_real_query(conn, final_query, strlen(final_query)) != 0) {
    debug_print("_nss_maria_getspnam_r cannot execute getpwnam mariadb query");
    log_mysql_error(conn);
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_RES *result = mysql_store_result(conn);

  if(result == NULL) {
    debug_print("_nss_maria_getspnam_r cannot get result from query");
    free(settings);
    free(name_sanitized);
    free(final_query);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_ROW row = mysql_fetch_row(result);

  if (row == NULL) {
    debug_print("_nss_maria_getspnam_r no result found");
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

  result_buf->sp_namp = xname;
  result_buf->sp_pwdp = password;
  result_buf->sp_lstchg = strtol(row[2], NULL, 10);
  result_buf->sp_min = strtol(row[3], NULL, 10);
  result_buf->sp_max = strtol(row[4], NULL, 10);
  result_buf->sp_warn = strtol(row[5], NULL, 10);
  result_buf->sp_inact = strtol(row[6], NULL, 10);
  result_buf->sp_expire = strtol(row[7], NULL, 10);
  result_buf->sp_flag = strtoul(row[8], NULL, 10);

  free(settings);
  free(name_sanitized);
  free(final_query);
  mysql_free_result(result);
  return NSS_STATUS_SUCCESS;
}
