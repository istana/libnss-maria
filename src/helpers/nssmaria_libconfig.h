#include <libconfig.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h>
#include <stdio.h>
#include <errno.h>
#include "../models/nssmaria_configurations.h"

void nss_maria_initialize_nssconfig(Nssmaria_configuration *config);
void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector);
int nss_maria_populate_nssconfig_from_libconfig_file(char *libconfig_filepath, Nssmaria_configuration *nss_config);
