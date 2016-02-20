#define NSSMARIACONFIG "/etc/libnss-maria.conf"
#include <libconfig.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct Nssmaria_configs {
  char dbhost[1024];
  unsigned int dbport;
  char dbuser[1024];
  char dbpass[1024];
  char dbname[1024];

  // "password" SQL queries
  // get user by name
  char getpwnam[8192];
  // get user by id
  char getpwuid[8192];
  // get all users
  char getpwent[8192];

  // shadow SQL queries
  // get shadow item by name
  char getspnam[8192];
  // get all shadow items
  char getspent[8192];

  // group SQL queries
  // get group by name
  char getgrnam[8192];
  // get group by id
  char getgrid[8192];
  // get groups
  char getgrent[8192];

  // not in glibc - get users by group id
  char memsbygid[8192];

  // not in glibc - get groups by user name
  char gidsbymem[8192];

} Nssmaria_config;


void nss_maria_initialize_config(Nssmaria_config *config) {
  strncpy(config->dbhost, "localhost", 1023);
  strncpy(config->dbuser, "root", 1023);
  strncpy(config->dbpass, "", 1023);
  strncpy(config->dbname, "libnss_maria", 1023);
  config->dbport = 3309;

  config->getpwnam[0] = config->getpwuid[0] = config->getpwent[0] = '\0';
  config->getspnam[0] = config->getspent[0] = '\0';
  config->getgrnam[0] = config->getgrid[0] = config->getgrent[0] = '\0';
  config->memsbygid[0] = config->gidsbymem[0] = '\0';
}

int nss_maria_populate_config_from_file(char *filepath, Nssmaria_config *config) {
  FILE* config_stream = fopen(filepath, "r");

  if(config_stream != NULL) {
    // parse libconfig file
    config_t config_nssmaria;
    config_init(&config_nssmaria);

    if(config_read(&config_nssmaria, config_stream) == CONFIG_TRUE) {
      printf("ok");

      return 0;
    } else {
      printf("error found in file %s, message: %s on line: %i",
        filepath,
        config_error_text(&config_nssmaria),
        config_error_line(&config_nssmaria)
      );
      return 1;
    }

    config_destroy (&config_nssmaria);
  } else {
    printf("Opening file : Failed\n");
    printf ("Error no is : %d\n", errno);
    printf("Error description is : %s\n",strerror(errno));
  }

  fclose(config_stream);
}

/*




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