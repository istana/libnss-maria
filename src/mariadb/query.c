#include "./query.h"

enum nss_status maria_query_with_param(
  const char *caller,
  char *query,
  char *param,
  Maria_config *settings,
  MYSQL **conn,
  MYSQL_RES **result,
  int *errnop
) {
  const char *placeholder = memchr(query, '?', strlen(query));

  if(!placeholder) {
    debug_print("placeholder not found in database query");
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  *conn = mysql_init(NULL);
  if(!*conn) {
    debug_print("mysql init failed, out of memory");
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }

  if(mysql_real_connect(
    *conn,
    settings->dbhost,
    settings->dbuser,
    settings->dbpass,
    settings->dbname,
    settings->dbport,
    NULL,
    0
  ) == NULL) {
    debug_print("cannot connect to the database");
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }
  
  char *param_sanitized = malloc((sizeof(char) * strlen(param) * 2) + 1);
  mysql_real_escape_string(*conn, param_sanitized, param, strlen(param));
  char *final_query = str_replace(query, "?", param_sanitized);
  debug_print_var(final_query);

  if (mysql_real_query(*conn, final_query, strlen(final_query)) != 0) {
    debug_print("cannot execute mariadb query");
    log_mysql_error(*conn);
    free(param_sanitized);
    free(final_query);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  *result = mysql_store_result(*conn);

  if(*result == NULL) {
    debug_print("cannot get result from query");
    log_mysql_error(*conn);
    free(param_sanitized);
    free(final_query);
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }

  free(param_sanitized);
  free(final_query);
  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_get_first_row(MYSQL **conn, MYSQL_RES **result, MYSQL_ROW *row, int *errnop) {
  *row = mysql_fetch_row(*result);

  if (*row == NULL) {
    debug_print("no result found");
    *errnop = ENOENT;
    return NSS_STATUS_NOTFOUND;
  }

  return NSS_STATUS_SUCCESS;
}
