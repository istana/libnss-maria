#include <criterion/criterion.h>
#include "configuration/maria_config.h"

Test(maria_config, maria_read_config_takes_values_from_file) {
  Maria_config *config = malloc(sizeof(*config));

  maria_read_config(config, "./test/fixtures/libnss-maria.conf", "./test/fixtures/libnss-maria-root.conf");
  cr_expect_str_eq(config->dbhost, "myrtana.sk");

  free(config);
}

Test(maria_config, maria_read_config_uses_default_value_if_not_present) {
  Maria_config *config = malloc(sizeof(*config));

  maria_read_config(config, "./test/fixtures/libnss-maria-light.conf", "./test/fixtures/libnss-maria-root-light.conf");
  cr_expect_str_eq(config->dbrootpass, "");

  free(config);
}
