#define LOG_ERROR(message) puts(message); return NSS_STATUS_UNAVAIL;

#define LOG_MYSQL_ERROR(message,mysql_handle) puts(message);\
printf("server information: %s\n", mysql_get_server_info(mysql_handle));\
printf("error number: %u, error: %s\n", mysql_errno(mysql_handle), mysql_error(mysql_handle));\
return NSS_STATUS_UNAVAIL;

#include "connection.h"

//todo: recommend connector c v3.x in build
MYSQL* maria_mariadb_connect(Maria_config *settings) {
  MYSQL *mysql_handle = mysql_init(NULL);

  // what to do with this?
  //if(!mysql_thread_safe()) { LOG_ERROR("environment is NOT threadsafe!") }
  if(mysql_handle == NULL) { LOG_ERROR("cannot initialize mysql") }

  MYSQL *connection = mysql_real_connect(
  	mysql_handle,
  	settings.dbhost,
  	settings.dbuser,
    settings.dbpass,
    settings.dbname,
    atoi(settings.dbport),
    NULL, // unix socket
    0
  );

  if(connection == NULL) { LOG_MYSQL_ERROR("could not connect to the database", mysql_handle) }

  return connection;
}


void maria_mariadb_disconnect(MYSQL *connection) {
  mysql_close(connection);
}
