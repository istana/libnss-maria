#include <criterion/criterion.h>
#include "helpers/nssmaria_libconfig.h"

Test(maria_config, initialize_config) {
  Nssmaria_configuration config;
  nss_maria_initialize_nssconfig(&config);

  cr_assert_str_eq(config.dbhost, "localhost");
  cr_assert_str_eq(config.dbname, "libnss_maria");
  cr_assert_str_eq(config.dbuser, "root");
  cr_assert_str_eq(config.dbpass, "");
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
  cr_assert_str_eq(config.gidsbymem, "");
}

Test(maria_config, populate_config_from_file) {
  Nssmaria_configuration config;
  nss_maria_initialize_nssconfig(&config);


  cr_assert_eq(nss_maria_populate_nssconfig_from_libconfig_file("./test/fixtures/libnss-maria.conf", &config), 0);
  cr_assert_str_eq(config.dbhost, "myrtana.sk");
  cr_assert_str_eq(config.dbname, "nss_maria");
  cr_assert_str_eq(config.dbuser, "doublelol");
  cr_assert_str_eq(config.dbpass, "Isabelle");
  cr_assert_str_eq(config.dbport, "9000");

  cr_assert_str_eq(config.getpwnam, "getpwnam test");
  cr_assert_str_eq(config.getpwuid, "getpwuid test");
  cr_assert_str_eq(config.getpwent, "getpwent test");

  cr_assert_str_eq(config.getspnam, "getspnam test");
  cr_assert_str_eq(config.getspent, "getspent test");

  cr_assert_str_eq(config.getgrnam, "getgrnam test");
  cr_assert_str_eq(config.getgrid, "getgrid test");
  cr_assert_str_eq(config.getgrent, "getgrent test");

  cr_assert_str_eq(config.memsbygid, "memsbygid test");
  cr_assert_str_eq(config.gidsbymem, "gidsbymem test");
}
