#include "libnss-maria.h"

struct nssmariaconfig {
	char host[255];
	char user[255];
	char passwd[255];
	char db[255];
	unsigned int port;
	char unix_socket[255];
};

enum nss_status _nss_maria_getpwnam_r(const char *name, struct passwd *pwd,
		char *buffer, size_t buflen, int *errnop) {

  struct nssmariaconfig c = { "localhost", "root", "", "nssmaria", 3306, "" };

	if(mysql_thread_safe() == 1) {
		puts("the environment is not threadsafe");
	}

	if(mysql_thread_init() == 0) {
		puts("threading could not have been initialized");
	}

	MYSQL *handle;
	MYSQL *xxx = mysql_init(handle);

	if(xxx == NULL) {
		puts("cannot initialize mysql");
		return 1;
	}

	MYSQL *connection = mysql_real_connect(handle, c.host, c.user, c.passwd, c.db, c.port, c.unix_socket, 0);

	if(connection == NULL) {
		puts("could not connect to the database");
	}

}
