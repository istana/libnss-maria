#include "nssmaria_libconfig.h"

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

void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector) {
  // is freed by libconfig
  const char *buffer = malloc(1024 * sizeof(char));

  if(config_lookup_string(&libconfig_object, selector, &buffer) == CONFIG_TRUE) {
    strncpy(destination, buffer, 1023);
  };
}
