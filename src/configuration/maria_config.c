#include "maria_config.h"

int maria_read_config_file(Maria_config* config, const char *path) {
  maria_initialize_config(config);
  return maria_set_config_from_file(path, config);
}
