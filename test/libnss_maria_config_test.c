#define STREQ(EXPECTED,GOT) assert(strncmp(#EXPECTED, GOT, 1024) == 0);

#include <stdio.h>
#include "libnss-maria.h"


int test_config() {
  Libnssmaria_config *config;
  libnss_maria_initialize_config(config);

  //ssmaria_load_config("fixtures/nssmaria_root.conf");
  //STREQ("hor.im", config.dbhost);
  //STREQ("root", config.dbuser);
  //STREQ("123456", config.dbpass);
}

int main(void) {

  puts("xxx");
  return 0;
}

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
