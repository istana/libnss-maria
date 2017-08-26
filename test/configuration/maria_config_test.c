#include <criterion/criterion.h>
#include "configuration/maria_config.h"

Test(maria_config, maria_read_config_file_takes_values_from_file) {
  Maria_config config = maria_read_config_file("./test/fixtures/libnss-maria.conf");
  cr_expect_str_eq(config.dbhost, "myrtana.sk");
}

Test(maria_config, maria_read_config_file_uses_default_value_if_not_present) {
  Maria_config config = maria_read_config_file("./test/fixtures/libnss-maria-light.conf");
  cr_expect_str_eq(config.dbhost, "localhost");
}
