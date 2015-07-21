#include "libnss-maria.h"

struct bla_conf {
	char host[255];
	char user[255];
	char passwd[255];
	char db[255];
	unsigned int port;
	char unix_socket[255];
} conf;

enum nss_status _nss_maria_getpwnam_r(const char *name, struct passwd *pwd,
		char *buffer, size_t buflen, int *errnop) {

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

	MYSQL *connection = mysql_real_connect(handle, conf.host, conf.user, conf.passwd, conf.db, conf.port, conf.unix_socket, 0);

	if(connection == NULL) {
		puts("could not connect to the database");
	}

}
