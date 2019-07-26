#ifndef MARIA_MARIADB_CONNECTION_H
#define MARIA_MARIADB_CONNECTION_H
#include <stdio.h>
#include <mysql.h>
#include <nss.h>

MYSQL* maria_mariadb_connect(Maria_config *settings);
MYSQL* maria_mariadb_disconnect(Maria_config *settings);

#endif
