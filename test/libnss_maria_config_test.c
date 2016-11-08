#include "libnss-maria.h"
#include <criterion/criterion.h>

Test(maria_config, initialize_config) {
  Nssmaria_configuration config;
  nss_maria_initialize_config(&config);


  cr_assert_str_eq(config.dbhost, "localhost");
  cr_assert_str_eq(config.dbuser, "root");
  cr_assert_str_eq(config.dbpass, "");
  cr_assert_str_eq(config.dbname, "libnss_maria");
  cr_assert_str_eq(config.dbport, "3309");

  cr_assert_str_eq(config.getpwnam, "");
  cr_assert_str_eq(config.getpwuid, "");
  cr_assert_str_eq(config.getpwent, "");

  cr_assert_str_eq(config.getspnam, "");
  cr_assert_str_eq(config.getspent, "");

  cr_assert_str_eq(config.getgrnam, "");
  cr_assert_str_eq(config.getgrid, "");
  cr_assert_str_eq(config.getgrent, "");

  cr_assert_str_eq(config.memsbygid, "");
  cr_assert_str_eq(config.getspnam, "");
  cr_assert_str_eq(config.gidsbymem, "");
}

Test(maria_config, populate_config_from_file_example_config) {
  Nssmaria_configuration config;
  nss_maria_initialize_config(&config);


  cr_assert_eq(nss_maria_populate_config_from_file("./test/fixtures/libconfig-example.conf", &config), 0);
}

Test(maria_config, populate_config_from_file) {
  Nssmaria_configuration config;
  nss_maria_initialize_config(&config);


  cr_assert_eq(nss_maria_populate_config_from_file("./test/fixtures/libnss-maria.conf", &config), 0);

  printf("%s", config.dbhost);
  cr_assert_str_eq(config.dbhost, "myrtana.sk");
  cr_assert_str_eq(config.dbname, "nss_maria");
  cr_assert_str_eq(config.dbuser, "unss_maria");
  cr_assert_str_eq(config.dbpass, "Isabelle");
  cr_assert_str_eq(config.dbport, "9000");

  cr_assert_str_eq(config.getpwnam, "SELECT users.username AS username, 'x' AS password, users.id AS uid, users.gid AS gid, \
users.gecos AS gecos, users.homedir AS homedir, users.shell AS shell FROM users INNER JOIN groups_users ON users.id = groups_users.user_id \
INNER JOIN groups ON groups_users.group_id = groups.id WHERE users.active = 1 AND users.gid = groups.id AND users.username = ? \
ORDER BY groups.id LIMIT 1");
}