#include "nssmaria_libconfig.h"

Nssmaria_configuration nss_maria_read_configuration_from_file(char *path) {
  Nssmaria_configuration settings;
  nss_maria_initialize_nssconfig(&settings);
  nss_maria_populate_nssconfig_from_libconfig_file(path, &settings);
  return settings;
}
