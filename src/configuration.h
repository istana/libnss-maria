#define NSSMARIACONFIG "/etc/libnss-maria.conf"
#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Nssmaria_configs {
  char dbhost[1024];
  char dbport[1024];
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
  strncpy(config->dbport, "3309", 1023);

  config->getpwnam[0] = config->getpwuid[0] = config->getpwent[0] = '\0';
  config->getspnam[0] = config->getspent[0] = '\0';
  config->getgrnam[0] = config->getgrid[0] = config->getgrent[0] = '\0';
  config->memsbygid[0] = config->gidsbymem[0] = '\0';
}

void nss_maria_load_setting(config_t conffile, char *dest, const char *path) {
  const char *buffer = malloc(1024 * sizeof(char));

  if(config_lookup_string(&conffile, path, &buffer) == CONFIG_TRUE) {
    strncpy(dest, buffer, 1023);
  };
}

int nss_maria_populate_config_from_file(char *filepath, Nssmaria_config *config) {
  FILE* config_stream = fopen(filepath, "r");

  if(config_stream != NULL) {
    // parse libconfig file
    config_t config_nssmaria;
    config_init(&config_nssmaria);

    if(config_read(&config_nssmaria, config_stream) == CONFIG_TRUE) {
      printf("ok");

      nss_maria_load_setting(config_nssmaria, config->dbhost, "database_settings.host");
      nss_maria_load_setting(config_nssmaria, config->dbname, "database_settings.database");
      nss_maria_load_setting(config_nssmaria, config->dbuser, "database_settings.username");
      nss_maria_load_setting(config_nssmaria, config->dbpass, "database_settings.password");
      nss_maria_load_setting(config_nssmaria, config->dbport, "database_settings.port");

      nss_maria_load_setting(config_nssmaria, config->getpwnam, "nss_queries.getpwnam");
      nss_maria_load_setting(config_nssmaria, config->getpwuid, "nss_queries.getpwuid");
      nss_maria_load_setting(config_nssmaria, config->getspnam, "nss_queries.getspnam");
      nss_maria_load_setting(config_nssmaria, config->getspent, "nss_queries.getspent");
      nss_maria_load_setting(config_nssmaria, config->getgrnam, "nss_queries.getgrnam");
      nss_maria_load_setting(config_nssmaria, config->getgrid, "nss_queries.getgrid");
      nss_maria_load_setting(config_nssmaria, config->getgrent, "nss_queries.getgrent");
      nss_maria_load_setting(config_nssmaria, config->memsbygid, "nss_queries.memsbygid");
      nss_maria_load_setting(config_nssmaria, config->gidsbymem, "nss_queries.gidsbymem");

      config_destroy (&config_nssmaria);
      return 0;
    } else {
      printf("error found in file %s, message: %s on line: %i",
        filepath,
        config_error_text(&config_nssmaria),
        config_error_line(&config_nssmaria)
      );
      config_destroy(&config_nssmaria);
      return 1;
    }
    
  } else {
    printf("Opening file : Failed\n");
    printf ("Error no is : %d\n", errno);
    printf("Error description is : %s\n",strerror(errno));
  }

  fclose(config_stream);
}
