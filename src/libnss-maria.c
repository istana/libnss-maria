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
  }

  mysql_close(mysql_handle);

  return 0;
}
