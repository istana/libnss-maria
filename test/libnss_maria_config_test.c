#include "libnss-maria.h"
#include <criterion/criterion.h>

Test(maria_config, initialize_config) {
  Nssmaria_config config;
  nss_maria_initialize_config(&config);

  cr_assert_str_eq(config.dbhost, "localhost");
  cr_assert_str_eq(config.dbuser, "root");
  cr_assert_str_eq(config.dbpass, "");
  cr_assert_str_eq(config.dbname, "libnss_maria");
  cr_assert_eq(config.dbport, 3309);

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



