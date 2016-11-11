#include <libconfig.h>
#include <stdlib.h>
#include <string.h>
#include "../models/nssmaria_configurations.h"

void nss_maria_initialize_config(Nssmaria_configuration *config);
void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector);
