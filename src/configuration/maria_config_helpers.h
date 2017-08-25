#ifndef MARIA_CONFIG_HELPERS_H
#define MARIA_CONFIG_HELPERS_H
#define NSSMARIACONFIG "/etc/libnss-maria.conf"

#include <libconfig.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "maria_config.h"
#include "../logger/maria_logger.h"

void maria_initialize_config(Maria_config *config);
void maria_load_setting(config_t libconfig_object, char *destination, const char *selector);
int maria_set_config_from_file(char *path, Maria_config *config);

#endif
