#include "maria_config.h"

int maria_read_config(Maria_config* config, const char *path, const char *root_path, int is_root) {
  maria_initialize_config(config);
  int read_result = 1;

  read_result = maria_set_config_from_file(path, config);

  if (read_result > 0) {
    return read_result;
  }

  if(is_root) {
    read_result = maria_set_root_config_from_file(root_path, config);
  }

  return read_result;
}
