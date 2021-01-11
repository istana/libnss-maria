#ifndef MARIA_NSS_SHADOW_H
#define MARIA_NSS_SHADOW_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql.h>
#include <nss.h>
#include <shadow.h>
#include <sys/types.h>
#include <threads.h>
#include "../logger/maria_logger.h"
#include "../configuration/maria_config.h"
#include "../mariadb/query.h"
#include "./result_handler.h"

enum nss_status _nss_maria_getspnam_r (
  const char *spnam,
  struct spwd *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_getspent_r (
  struct spwd *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_setspent (void);
enum nss_status _nss_maria_endspent (void);
#endif
