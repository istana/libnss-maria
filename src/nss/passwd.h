#ifndef MARIA_NSS_PASSWD_H
#define MARIA_NSS_PASSWD_H
#include <nss.h>
#include <pwd.h>
#include <sys/types.h>

/*
struct passwd {
  char    *pw_name;      // username
  char    *pw_passwd;    // user password
  uid_t    pw_uid;       // user ID
  gid_t    pw_gid;       // group ID
  char    *pw_gecos;     // user information
  char    *pw_dir;       // home directory
  char    *pw_shell;     // shell program
};
*/

enum nss_status _nss_maria_getpwnam_r (
  const char *name,
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);

enum nss_status _nss_maria_getpwuid_r (
  uid_t uid,
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);

enum nss_status _nss_maria_getpwent_r (
  struct passwd *result,
  char *buffer,
  size_t buflen,
  int *errnop
);

#endif
