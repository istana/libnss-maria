#include "maria_config.h"

int maria_read_config(Maria_config* config, const char *path, const char *root_path, int is_root) {
  maria_initialize_config(config);

  if(!is_root) {
    return maria_set_config_from_file(path, config);
  }

  return maria_set_root_config_from_file(root_path, config);
}
