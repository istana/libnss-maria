#include "maria_config.h"

Maria_config* maria_read_config_file(const char *path) {
  Maria_config settings;
  Maria_config *setting = &settings;
  maria_initialize_config(setting);
  maria_set_config_from_file(path, setting);
  return setting;
}
