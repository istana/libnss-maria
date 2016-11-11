#define NSSMARIACONFIG "/etc/libnss-maria.conf"

#include "../models/nssmaria_configurations.h"
#include "../helpers/nssmaria_libconfig.h"

Nssmaria_configuration nss_maria_read_configuration_from_file(char *path);
