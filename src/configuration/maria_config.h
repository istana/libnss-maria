#ifndef MARIA_CONFIG_H
#define MARIA_CONFIG_H
#include "maria_config_struct.h"
#include "maria_config_helpers.h"

int maria_read_config(Maria_config* config, const char *path, const char *root_path, int is_root);

#define READ_USER_CONFIG(is_root, errnop) \
  if(maria_read_config(settings, "/etc/libnss-maria.conf", "/etc/libnss-maria-root.conf", is_root) > 0) {\
    free(settings);\
    *errnop = ENOENT;\
    return NSS_STATUS_UNAVAIL;\
  }

#endif
