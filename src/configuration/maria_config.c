#include "maria_config.h"

Maria_config maria_read_config_file(char *path) {
  Maria_config settings;
  maria_initialize_config(&settings);
  maria_set_config_from_file(path, &settings);
  return settings;
}
