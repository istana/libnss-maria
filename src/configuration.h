#define NSSMARIACONFIG "/etc/libnss-maria.conf"
#include <libconfig.h>

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
