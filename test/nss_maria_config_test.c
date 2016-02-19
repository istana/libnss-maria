#define _TEST(code) if(code) { return 0; } else { return 1; }
#define STREQ(expected,got) assert(strncmp(#expected, got, 255) == 0);

#include <stdio.h>
#include "libnss-maria.h"


int test_config() {
  nssmaria_config *config = nssmaria_load_config("fixtures/nssmaria_root.conf");
  STREQ("hor.im", config.dbhost);
  STREQ("root", config.dbuser);
  STREQ("123456", config.dbpassword);
  STREQ

}


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





