#include "maria_config.h"

int maria_read_config(Maria_config* config, const char *path, const char *root_path, int is_root) {
  int root_config_ok = 0;

  maria_initialize_config(config);
  int config_ok = maria_set_config_from_file(path, config);

  if(is_root) {
    root_config_ok = maria_set_root_config_from_file(root_path, config);
  }

  return config_ok && root_config_ok;
}
