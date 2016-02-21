#include "libnss-maria.h"
#include <criterion/criterion.h>

Test(maria_config, getpwnam_r) {
	struct passwd pw;
	char buffer[255];
	int errno_number = 0;
	enum nss_status s = _nss_maria_getpwnam_r("bloodbornemisa", &pw, buffer, 255, &errno_number);
	printf("nss_status: %d", s);
}
