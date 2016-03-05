#include "libnss-maria.h"

enum nss_status _nss_maria_getpwnam_r(const char *name, struct passwd *pwd, char *buffer, size_t buflen, int *errnop) {

	if(mysql_thread_safe() == 1) {
		puts("the environment IS threadsafe");
	}

	MYSQL *mysql_handle = mysql_init(NULL);

	if(mysql_handle == NULL) {
		puts("cannot initialize mysql");
		return 1;
	}

  Nssmaria_config settings = nss_maria_read_config_from_file("./test/fixtures/connection_test.conf");

  MYSQL *connection = mysql_real_connect(mysql_handle, settings.dbhost, settings.dbuser,
    settings.dbpass, settings.dbname, atoi(settings.dbport), NULL, 0
  );

  if(connection == NULL) {
    puts("could not connect to the database");
    printf("server information: %s", mysql_get_server_info(mysql_handle));
    printf("error number: %u, error: %s\n", mysql_errno(mysql_handle), mysql_error(mysql_handle));
    return 10;
  }



  MYSQL_STMT *statement = mysql_stmt_init(connection);

  if(statement == NULL) {
    puts("could not connect to the database");
    return 10;
  }

  if(mysql_stmt_prepare(statement, settings.getpwnam, strlen(settings.getpwnam)) != 0) {
    puts("cannot prepare statement");
    return 10;
  }

  MYSQL_BIND bind[1];

  bind[0].buffer_type = MYSQL_TYPE_STRING;
  bind[0].buffer = "testuserXXX";
  bind[0].buffer_length = strlen("testuserXXX");

  bind[0].is_null = (my_bool*)0;
  bind[0].length = 0;
  bind[0].is_unsigned = 0;

  if(mysql_stmt_bind_param(statement, bind) != 0) {
    puts("cannot bind params");
    return 10;
  }

  if (mysql_stmt_execute(statement))
  {
    fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(statement));
    exit(0);
  }

  /* Get the number of affected rows */
  uint affected_rows = mysql_stmt_affected_rows(statement);
  fprintf(stdout, " total affected rows(insert 1): %lu\n",
                  (unsigned long) affected_rows);



  mysql_stmt_close(statement);
  mysql_close(mysql_handle);

  return 0;
}
