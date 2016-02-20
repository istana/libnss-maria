#include "libnss-maria.h"
#include <criterion/criterion.h>

Test(suite_name, test_name) {
  // test contents
  cr_expect(strlen("Test") == 4, "Expected \"Test\" to have a length of 4.");
  cr_expect(strlen("Hello") == 4, "This will always fail, why did I add this?");
  cr_assert(strlen("") == 0);
}

/*
int test_libnss_maria_initialize_config(void) {
  Libnssmaria_config *config;
  libnss_maria_initialize_config(config);

  STREQ("localhost", config->dbhost);

}


int test_config() {
  Libnssmaria_config *config;
  libnss_maria_initialize_config(config);

  //ssmaria_load_config("fixtures/nssmaria_root.conf");
  //STREQ("hor.im", config.dbhost);
  //STREQ("root", config.dbuser);
  //STREQ("123456", config.dbpass);
}

int main(void) {
  test_libnss_maria_initialize_config();

  puts("xxx");
  return 0;
}
*/
/*
int UNITTEST()




int main(void) {
  RUN_TESTS
  n nssmaria_config *config = nssmaria_load_config("fixtures/nssmaria_root.conf");ssmaria_config *config = nssmaria_load_config("fixtures/nssmaria_root.conf");

  if
  //string* config = libnssmaria_load_config();
  return 0;
}

int main(void) {
  printf("Hello world\n");
        test__nss_maria_getpwnam_r();
}

*/
