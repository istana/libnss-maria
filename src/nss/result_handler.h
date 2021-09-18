#ifndef MARIA_NSS_RESULT_HANDLER_H
#define MARIA_NSS_RESULT_HANDLER_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <nss.h>
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <mysql.h>
#include "../logger/maria_logger.h"

enum nss_status copy_db_row_to_passwd(
  MYSQL_RES *passwd_query_result,
  MYSQL_ROW_OFFSET passwd_db_initial_offset,
  MYSQL_ROW row,
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop
);
enum nss_status copy_db_row_to_shadow(
  MYSQL_RES *shadow_query_result,
  MYSQL_ROW_OFFSET shadow_db_initial_offset,
  MYSQL_ROW row,
  struct spwd *shadow_result,
  char *buffer,
  size_t buflen,
  int *errnop
);
enum nss_status copy_db_row_to_group(
  MYSQL_RES *group_query_result,
  MYSQL_ROW_OFFSET group_query_initial_offset,
  MYSQL_ROW row,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  size_t *occupied_buffer,
  int *errnop
);
enum nss_status copy_group_members_to_group(
  MYSQL_RES *group_query_result,
  MYSQL_ROW_OFFSET group_db_initial_offset,
  MYSQL_RES *members_query_result,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  size_t *occupied_buffer,
  int *errnop
);
enum nss_status copy_gids(
  MYSQL_RES *result,
  MYSQL_ROW_OFFSET result_initial_offset,
  long int *start_index,
  long int *gids_size,
  gid_t **gids,
  long int limit,
  int *errnop
);

#define CLEANUP() \
  if(settings != NULL) free(settings);\
  if(result != NULL) mysql_free_result(result);\
  if(conn != NULL) mysql_close(conn);

#endif
