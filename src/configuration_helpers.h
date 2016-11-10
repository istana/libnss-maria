#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector);
int nss_maria_populate_config_from_file(char *libconfig_filepath, Nssmaria_configuration *nss_config);
