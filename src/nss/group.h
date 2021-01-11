#ifndef MARIA_NSS_GROUP_H
#define MARIA_NSS_GROUP_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql.h>
#include <nss.h>
#include <grp.h>
#include <sys/types.h>
#include <threads.h>
#include "../logger/maria_logger.h"
#include "../configuration/maria_config.h"
#include "../mariadb/query.h"
#include "./result_handler.h"

enum nss_status _nss_maria_getgrnam_r (
  const char *name,
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_getgrgid_r (
  uid_t id,
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_initgroups_dyn (
  const char *username,
  gid_t gid,
  long int *start_index,
  long int *gids_size,
  gid_t **gids,
  long int limit,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_getgrent_r (
  struct group *result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
);
enum nss_status _nss_maria_setgrent (void);
enum nss_status _nss_maria_endgrent (void);
#endif
