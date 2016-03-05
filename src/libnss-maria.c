#define LOG_MYSQL_ERROR(message,mysql_handle) puts(message);\
printf("server information: %s\n", mysql_get_server_info(mysql_handle));\
printf("error number: %u, error: %s\n", mysql_errno(mysql_handle), mysql_error(mysql_handle));\
return NSS_STATUS_UNAVAIL;

#define LOG_MYSQL_STATEMENT_ERROR(message,stmt,handle) puts(message);\
printf("server information: %s\n", mysql_get_server_info(mysql_handle));\
printf("error number: %u, error: %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));\
return NSS_STATUS_UNAVAIL;

#define LOG_ERROR(message) puts(message); return NSS_STATUS_UNAVAIL;

#include "libnss-maria.h"

/* nss.h
enum nss_status
{
  NSS_STATUS_TRYAGAIN = -2,
  NSS_STATUS_UNAVAIL,
  NSS_STATUS_NOTFOUND,
  NSS_STATUS_SUCCESS,
  NSS_STATUS_RETURN
};*/
 
enum nss_status _nss_maria_getpwnam_r(const char *name, struct passwd *pwd, char *buffer, size_t buflen, int *errnop) {

  Nssmaria_config settings = nss_maria_read_config_from_file("./test/fixtures/connection_test.conf");

	if(!mysql_thread_safe()) { LOG_ERROR("environment is NOT threadsafe!") }

	MYSQL *mysql_handle = mysql_init(NULL);
	if(mysql_handle == NULL) { LOG_ERROR("cannot initialize mysql") }

  MYSQL *connection = mysql_real_connect(mysql_handle, settings.dbhost, settings.dbuser,
    settings.dbpass, settings.dbname, atoi(settings.dbport), NULL, 0
  );
  if(connection == NULL) { LOG_MYSQL_ERROR("could not connect to the database", mysql_handle) }

  MYSQL_STMT *statement = mysql_stmt_init(connection);
  if(statement == NULL) {
    LOG_MYSQL_STATEMENT_ERROR("cannot allocate memory for prepared statement", statement, mysql_handle);
  }

  if(mysql_stmt_prepare(statement, settings.getpwnam, strlen(settings.getpwnam))) {
    LOG_MYSQL_STATEMENT_ERROR("cannot prepare statement", statement, mysql_handle);
  }

  MYSQL_BIND bind[1];

  bind[0].buffer_type = MYSQL_TYPE_STRING;
  bind[0].buffer = "testuserXXX";
  bind[0].buffer_length = strlen("testuserXXX");

  bind[0].is_null = (my_bool*)0;
  bind[0].length = 0;
  bind[0].is_unsigned = 0;

  if(mysql_stmt_bind_param(statement, bind)) {
    LOG_MYSQL_STATEMENT_ERROR("cannot bind params", statement, mysql_handle);
  }

  if (mysql_stmt_execute(statement))
  {
    LOG_MYSQL_STATEMENT_ERROR("cannot execute query", statement, mysql_handle);
  }

  /* Get the number of affected rows */
  uint affected_rows = mysql_stmt_affected_rows(statement);
  fprintf(stdout, " total affected rows(insert 1): %lu\n",
                  (unsigned long) affected_rows);



  mysql_stmt_close(statement);
  mysql_close(mysql_handle);

  return 0;
}
