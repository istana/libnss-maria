#ifndef MARIA_CONFIG_HELPERS_H
#define MARIA_CONFIG_HELPERS_H

#include <libconfig.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "maria_config_struct.h"
#include "../logger/maria_logger.h"

void maria_initialize_config(Maria_config *config);
void maria_load_string_setting(config_t libconfig_object, char *destination, const char *selector);
void maria_load_int64_setting(config_t libconfig_object, long long *destination, const char *selector);
int maria_set_config_from_file(const char *path, Maria_config *config);
int maria_set_root_config_from_file(const char *path, Maria_config *config);

#endif
