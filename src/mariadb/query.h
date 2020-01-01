#ifndef MARIA_MARIADB_QUERY_H
#define MARIA_MARIADB_QUERY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <nss.h>
#include <errno.h>
#include "../logger/maria_logger.h"
#include "../configuration/maria_config_struct.h"
#include "../str_replace.h"
#include "../mariadb/query.h"

enum nss_status maria_init_db_conn(Maria_config *settings, MYSQL **conn, int *errnop);
enum nss_status maria_do_query(MYSQL *conn, char *query, int *errnop);
enum nss_status maria_get_result(MYSQL *conn, MYSQL_RES **result, int *errnop);
enum nss_status maria_query_with_param(
  const char *caller,
  char *query,
  char *param,
  Maria_config *settings,
  MYSQL **conn,
  MYSQL_RES **result,
  int *errnop
);
enum nss_status maria_query_no_param(
  const char *caller,
  char *query,
  Maria_config *settings,
  MYSQL **conn,
  MYSQL_RES **result,
  int *errnop
);
enum nss_status maria_get_first_row(MYSQL **conn, MYSQL_RES **result, MYSQL_ROW *row, int *errnop);
#endif
