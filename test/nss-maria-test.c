#include <stdio.h>
#include "libnss-maria.h"

int test__nss_maria_getpwnam_r(void) {
	struct passwd pw;
	char buffer[255];
	int errno = 0;
	enum nss_status s = _nss_maria_getpwnam_r("ivan", &pw, buffer, 255, &errno);
	printf("nss_status: %d", s);
	return 0;
}


int test_configuration(void) {

  //string* config = libnssmaria_load_config();
  return 0;
}

int main(void) {
  printf("Hello world\n");
	test__nss_maria_getpwnam_r();
}


