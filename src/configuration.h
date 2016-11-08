#define NSSMARIACONFIG "/etc/libnss-maria.conf"
#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Nssmaria_configurations {
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

} Nssmaria_configuration;


void nss_maria_initialize_config(Nssmaria_configuration *config) {
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

/* internal */
void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector) {
  const char *buffer = malloc(1024 * sizeof(char));

  if(config_lookup_string(&libconfig_object, selector, &buffer) == CONFIG_TRUE) {
    strncpy(destination, buffer, 1023);
  };

  free(buffer);
}

int nss_maria_populate_config_from_file(char *libconfig_filepath, Nssmaria_configuration *nss_config) {
  FILE* libconfig_stream = fopen(libconfig_filepath, "r");

  if(libconfig_stream != NULL) {
    // parse libconfig file
    config_t libconfig_object;
    config_init(&libconfig_object);

    if(config_read(&libconfig_object, libconfig_stream) == CONFIG_TRUE) {
      printf("ok");

      nss_maria_load_setting(libconfig_object, nss_config->dbhost, "database_settings.host");
      nss_maria_load_setting(libconfig_object, nss_config->dbname, "database_settings.database");
      nss_maria_load_setting(libconfig_object, nss_config->dbuser, "database_settings.username");
      nss_maria_load_setting(libconfig_object, nss_config->dbpass, "database_settings.password");
      nss_maria_load_setting(libconfig_object, nss_config->dbport, "database_settings.port");

      nss_maria_load_setting(libconfig_object, nss_config->getpwnam, "nss_queries.getpwnam");
      nss_maria_load_setting(libconfig_object, nss_config->getpwuid, "nss_queries.getpwuid");
      nss_maria_load_setting(libconfig_object, nss_config->getspnam, "nss_queries.getspnam");
      nss_maria_load_setting(libconfig_object, nss_config->getspent, "nss_queries.getspent");
      nss_maria_load_setting(libconfig_object, nss_config->getgrnam, "nss_queries.getgrnam");
      nss_maria_load_setting(libconfig_object, nss_config->getgrid, "nss_queries.getgrid");
      nss_maria_load_setting(libconfig_object, nss_config->getgrent, "nss_queries.getgrent");
      nss_maria_load_setting(libconfig_object, nss_config->memsbygid, "nss_queries.memsbygid");
      nss_maria_load_setting(libconfig_object, nss_config->gidsbymem, "nss_queries.gidsbymem");

      config_destroy (&libconfig_object);
      return 0;
    } else {
      printf("error found in file %s, message: %s on line: %i",
        libconfig_filepath,
        config_error_text(&libconfig_object),
        config_error_line(&libconfig_object)
      );
      config_destroy(&libconfig_object);
      return 1;
    }
  } else {
    printf("Opening file : Failed\n");
    printf ("Error no is : %d\n", errno);
    printf("Error description is : %s\n", strerror(errno));
    return 1;
  }

  fclose(libconfig_stream);
}

Nssmaria_configuration nss_maria_read_config_from_file(char *path) {
  Nssmaria_configuration settings;
  nss_maria_initialize_config(&settings);
  nss_maria_populate_config_from_file(path, &settings);
  return settings;
}