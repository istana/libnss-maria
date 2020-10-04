#include "./query.h"

enum nss_status maria_init_db_conn(Maria_config *settings, MYSQL **conn, int *errnop, int use_root_user) {
  *conn = mysql_init(NULL);
  if(!*conn) {
    maria_log("mysql init failed, out of memory");
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }

  if(strlen(settings->mariadb_client_config) == 0) {
    debug_print("custom mariadb client config file not specified");
  } else if (mysql_optionsv(*conn, MYSQL_READ_DEFAULT_FILE, (void *)settings->mariadb_client_config)) {
    maria_log("cannot load mariadb client options");
    log_mysql_error(*conn);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  } else {
    debug_print("custom options file loaded");
  }


  if(mysql_real_connect(
    *conn,
    settings->dbhost,
    use_root_user ? settings->dbrootuser : settings->dbuser,
    use_root_user ? settings->dbrootpass : settings->dbpass,
    settings->dbname,
    settings->dbport,
    settings->unix_socket,
    0
  ) == NULL) {
    maria_log("cannot connect to the database");
    maria_log("settings;dbhost:%s;dbname:%s;db(root)user:%s;db(root)pass:%s;dbport:%lld;unix_socket:%s;mariadb_client_config:%s",
      settings->dbhost,
      settings->dbname,
      use_root_user ? settings->dbrootuser : settings->dbuser,
      use_root_user ? settings->dbrootpass : settings->dbpass,
      settings->dbport,
      strlen(settings->unix_socket) == 0 ? NULL : settings->unix_socket,
      settings->mariadb_client_config
    );
    log_mysql_error(*conn);
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }

  char encoding[] = "utf8";
  if (mysql_set_character_set(*conn, encoding) == 0) {
    debug_print_var("character set set to %s", encoding);
  } else {
    maria_log("cannot set character set to %s", encoding);
  }

  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_do_query(MYSQL *conn, const char *query, int *errnop) {
  if (mysql_real_query(conn, query, strlen(query)) != 0) {
    maria_log("cannot execute mariadb query");
    log_mysql_error(conn);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_get_result(MYSQL *conn, MYSQL_RES **result, int *errnop) {
  *result = mysql_store_result(conn);

  if(*result == NULL) {
    maria_log("cannot get result from query");
    log_mysql_error(conn);
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  }

  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_query_with_param(
  const char *caller,
  const char *query,
  const char *param,
  Maria_config *settings,
  MYSQL **conn,
  MYSQL_RES **result,
  int *errnop,
  int use_root_user
) {
  enum nss_status conn_status;
  enum nss_status reset_conn_status;
  enum nss_status query_status;
  enum nss_status result_status;

  if(!memchr(query, '?', strlen(query))) {
    maria_log("placeholder not found in database query, %s", caller);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  if(*conn != NULL) {
    if((reset_conn_status = maria_reset_connection(conn, errnop)) != NSS_STATUS_SUCCESS) {
      return reset_conn_status;
    }
  } else if((conn_status = maria_init_db_conn(settings, conn, errnop, use_root_user)) != NSS_STATUS_SUCCESS) {
    return conn_status;
  }

  char *param_sanitized = malloc((sizeof(char) * strlen(param) * 2) + 1);
  mysql_real_escape_string(*conn, param_sanitized, param, strlen(param));
  char *final_query = str_replace(query, "?", param_sanitized);
  debug_print_var(final_query);

  if((query_status = maria_do_query(*conn, final_query, errnop)) != NSS_STATUS_SUCCESS) {
    free(param_sanitized);
    free(final_query);
    return query_status;
  };

  if((result_status = maria_get_result(*conn, result, errnop)) != NSS_STATUS_SUCCESS) {
    free(param_sanitized);
    free(final_query);
    return result_status;
  };

  free(param_sanitized);
  free(final_query);
  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_query_no_param(
  const char *caller,
  const char *query,
  Maria_config *settings,
  MYSQL **conn,
  MYSQL_RES **result,
  int *errnop,
  int use_root_user
) {
  enum nss_status conn_status;
  enum nss_status reset_conn_status;
  enum nss_status query_status;
  enum nss_status result_status;

  if(*conn != NULL) {
    if((reset_conn_status = maria_reset_connection(conn, errnop)) != NSS_STATUS_SUCCESS) {
      return reset_conn_status;
    }
  } else if((conn_status = maria_init_db_conn(settings, conn, errnop, use_root_user)) != NSS_STATUS_SUCCESS) {
    return conn_status;
  }

  if((query_status = maria_do_query(*conn, query, errnop)) != NSS_STATUS_SUCCESS) {
    return query_status;
  };

  if((result_status = maria_get_result(*conn, result, errnop)) != NSS_STATUS_SUCCESS) {
    return result_status;
  };

  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_get_row(MYSQL **conn, MYSQL_RES **result, MYSQL_ROW *row, int *errnop) {
  *row = mysql_fetch_row(*result);

  if (*row == NULL) {
    debug_print("no result found");
    *errnop = ENOENT;
    return NSS_STATUS_NOTFOUND;
  }

  return NSS_STATUS_SUCCESS;
}

enum nss_status maria_reset_connection(MYSQL **conn, int *errnop) {
  if(mysql_reset_connection(*conn) > 0) {
    debug_print("issues resetting database connection");
    log_mysql_error(*conn);
    *errnop = EAGAIN;
    return NSS_STATUS_TRYAGAIN;
  } else {
    debug_print("db connection was reset");
  }

  return NSS_STATUS_SUCCESS;
}
