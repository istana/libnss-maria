#ifndef MARIA_CONFIG_H
#define MARIA_CONFIG_H
#include "maria_config_struct.h"
#include "maria_config_helpers.h"

int maria_read_config(Maria_config* config, const char *path, const char *root_path);

#endif
