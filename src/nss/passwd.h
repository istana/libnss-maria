#ifndef MARIA_NSS_PASSWD_H
#define MARIA_NSS_PASSWD_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql.h>
#include <nss.h>
#include <pwd.h>
#include <sys/types.h>
#include <threads.h>
#include "../logger/maria_logger.h"
#include "../configuration/maria_config.h"
#include "../str_replace.h"
#include "../mariadb/query.h"
#include "./result_handler.h"

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

enum nss_status _nss_maria_setpwent (void);

enum nss_status _nss_maria_getpwent_r (
  struct passwd *result,
  char *buffer,
  size_t buflen,
  int *errnop
);

enum nss_status _nss_maria_endpwent (void);
#endif
