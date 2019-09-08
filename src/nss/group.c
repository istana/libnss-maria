#include "./group.h"

enum nss_status _nss_maria_setgrent (void) {
  maria_log("_nss_maria_setgrent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_endgrent (void) {
  maria_log("_nss_maria_endgrent called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getgrent_r (
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getgrent_r called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getgrnam_r (
  const char *name,
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getgrnam_r called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_getgrgid_r (
  uid_t id,
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_getgrgid_r called!");
  return NSS_STATUS_NOTFOUND;
}

enum nss_status _nss_maria_initgroups_dyn (
  const char *user,
  gid_t group,
  long int *start,
  long int *size,
  gid_t **groupsp,
  long int limit,
  int *errnop,
  int *h_errnop
) {
  maria_log("_nss_maria_initgroups_dyn called!");
  return NSS_STATUS_NOTFOUND;
}
