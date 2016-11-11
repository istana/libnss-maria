#define NSSMARIACONFIG "/etc/libnss-maria.conf"

#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "models/nssmaria_configurations.h"
#include "helpers/nssmaria_libconfig.h"

Nssmaria_configuration nss_maria_read_config_from_file(char *path);
int nss_maria_populate_config_from_file(char *libconfig_filepath, Nssmaria_configuration *nss_config);
