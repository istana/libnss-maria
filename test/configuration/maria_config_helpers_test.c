#include <criterion/criterion.h>
#include "configuration/maria_config_helpers.h"

Test(maria_config_helpers, initialize_config_dbhost) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbhost, "localhost");
}

Test(maria_config_helpersx, initialize_config_dbname) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbname, "libnss_maria");
}

Test(maria_config_helpers, initialize_config_dbuser) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbuser, "root");
}

Test(maria_config_helpers, initialize_config_dbpass) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbpass, "");
}

Test(maria_config_helpers, initialize_config_dbport) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_eq(config.dbport, 3306);
}

Test(maria_config_helpers, initialize_config_unix_socket) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.unix_socket, "");
}

Test(maria_config_helpers, initialize_config_dbrootuser) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbrootuser, "");
}

Test(maria_config_helpers, initialize_config_dbrootpass) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.dbrootpass, "");
}

Test(maria_config_helpers, initialize_config_mariadb_client_config) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.mariadb_client_config, "");
}

Test(maria_config_helpers, initialize_config_getpwnam) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getpwnam, "");
}

Test(maria_config_helpers, initialize_config_getpwuid) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getpwuid, "");
}

Test(maria_config_helpers, initialize_config_getpwent) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getpwent, "");
}

Test(maria_config_helpers, initialize_config_getspnam) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getspnam, "");
}

Test(maria_config_helpers, initialize_config_getspent) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getspent, "");
}

Test(maria_config_helpers, initialize_config_getgrnam) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getgrnam, "");
}

Test(maria_config_helpers, initialize_config_getgrgid) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getgrgid, "");
}

Test(maria_config_helpers, initialize_config_getgrent) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.getgrent, "");
}

Test(maria_config_helpers, initialize_config_memsbygid) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.memsbygid, "");
}

Test(maria_config_helpers, initialize_config_gidsbymem) {
  Maria_config config;
  maria_initialize_config(&config);
  cr_expect_str_eq(config.gidsbymem, "");
}




Test(maria_config_helpers, maria_set_config_from_file_success) {
  Maria_config config;
  int return_value = maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_eq(return_value, 0);
}

Test(maria_config_helpers, maria_set_config_from_file_dbhost) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.dbhost, "myrtana.sk");
}

Test(maria_config_helpers, maria_set_config_from_file_dbname) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.dbname, "nss_maria");
}

Test(maria_config_helpers, maria_set_config_from_file_dbuser) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.dbuser, "doublelol");
}

Test(maria_config_helpers, maria_set_config_from_file_dbpass) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.dbpass, "Isabelle");
}

Test(maria_config_helpers, maria_set_config_from_file_dbport) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_eq(config.dbport, 9000);
}

Test(maria_config_helpers, maria_set_config_from_file_unix_socket) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.unix_socket, "/var/run/mysqld/mysqld.sock");
}

Test(maria_config_helpers, maria_set_config_from_file_mariadb_client_config) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.mariadb_client_config, "/etc/libnss-maria-client-config.cnf");
}

Test(maria_config_helpers, maria_set_config_from_file_getpwnam) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getpwnam, "getpwnam test");
}

Test(maria_config_helpers, maria_set_config_from_file_getpwuid) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getpwuid, "getpwuid test");
}

Test(maria_config_helpers, maria_set_config_from_file_getpwent) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getpwent, "getpwent test");
}

Test(maria_config_helpers, maria_set_config_from_file_getspnam) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getspnam, "getspnam test");
}

Test(maria_config_helpers, maria_set_config_from_file_getspent) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getspent, "getspent test");
}

Test(maria_config_helpers, maria_set_config_from_file_getgrnam) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getgrnam, "getgrnam test");
}

Test(maria_config_helpers, maria_set_config_from_file_getgrgid) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getgrgid, "getgrgid test");
}

Test(maria_config_helpers, maria_set_config_from_file_getgrent) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.getgrent, "getgrent test");
}

Test(maria_config_helpers, maria_set_config_from_file_memsbygid) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.memsbygid, "memsbygid test");
}

Test(maria_config_helpers, maria_set_config_from_file_gidsbymem) {
  Maria_config config;
  maria_set_config_from_file("./test/fixtures/libnss-maria.conf", &config);
  cr_expect_str_eq(config.gidsbymem, "gidsbymem test");
}




Test(maria_config_helpers, maria_set_root_config_from_file_success) {
  Maria_config config;
  int return_value = maria_set_root_config_from_file("./test/fixtures/libnss-maria-root.conf", &config);
  cr_expect_eq(return_value, 0);
}

Test(maria_config_helpers, maria_set_root_config_from_file_dbrootuser) {
  Maria_config config;
  maria_set_root_config_from_file("./test/fixtures/libnss-maria-root.conf", &config);
  cr_expect_str_eq(config.dbrootuser, "iamreckless");
}

Test(maria_config_helpers, maria_set_root_config_from_file_dbrootpass) {
  Maria_config config;
  maria_set_root_config_from_file("./test/fixtures/libnss-maria-root.conf", &config);
  cr_expect_str_eq(config.dbrootpass, "Catherine");
}
