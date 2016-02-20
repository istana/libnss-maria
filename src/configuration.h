#define NSSMARIACONFIG "/etc/libnss-maria.conf"
#include <libconfig.h>
#include <string.h>

typedef struct Libnssmaria_configs {
  char dbhost[1024];
  unsigned int dbport;
  char dbuser[1024];
  char dbpass[1024];
  char dbname[1024];
} Libnssmaria_config;


void libnss_maria_initialize_config(Libnssmaria_config *config) {
  strncpy(config->dbhost, "localhost", 1023);
  config->dbport = 3309;
  strncpy(config->dbuser, "root", 1023);
  strncpy(config->dbpass, "", 1023);
  strncpy(config->dbname, "libnss_maria", 1023);
}

/*
config_t *nssconfig;
config_init(nssconfig);

if(config_read_file(nssconfig, NSSMARIACONFIG)) {



} else {
  puts("error found in file %s, message: %s on line: %i", config_error_file(nssconfig), config_error_text(nssconfig), config_error_line(nsconfig));
}

config_setting_t *database_config, *nss_queries;

database_config = config_lookup(nssconfig, "database_config");
nss_queries = config_lookup(nssconfig, "nssqueries");

if(database_config == NULL) { 
  puts ()
}


char *dbname, ;
config_lookup_string(nssconfig, "database", &dbname);

config_destroy(nssconfig);
*/