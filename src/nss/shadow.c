#include "./shadow.h"

enum nss_status _nss_maria_setspent (void) {
  maria_log("_nss_maria_setspent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_endspent (void) {
  maria_log("_nss_maria_endspent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getspent_r (
  struct spwd *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getspent_r called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getspnam_r(
  const char *spnam,
  struct spwd *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getspnam_r called!");
  return NSS_STATUS_NOTFOUND;
}
