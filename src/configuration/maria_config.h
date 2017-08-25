/*
the configuration file uses libconfig library (syntax), i.e. is nginx-like
TODO: config.h and config_helpers.h are tangled bidirectionally even though
  config_helpers should not call config.h at all
*/

#ifndef MARIA_CONFIG_H
#define MARIA_CONFIG_H
#include "maria_config_struct.h"
#include "maria_config_helpers.h"

Maria_config maria_read_config_file(char *path);

#endif
