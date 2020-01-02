#include "./group.h"

thread_local MYSQL *group_dbconn;
thread_local MYSQL_RES *group_dbresult;
thread_local MYSQL_ROW_OFFSET *group_cursor;

enum nss_status _nss_maria_getgrnam_r (
  const char *name,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrnam_r called!");

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_RES *group_members_result;
  MYSQL_ROW row;
  size_t occupied_buffer = 0;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getgrnam_r",
    settings->getgrnam,
    name,
    settings,
    &conn,
    &result,
    errnop
  );

  if (status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return status;
  }

  enum nss_status row_status = maria_get_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_group(row, group_result, buffer, buflen, &occupied_buffer, errnop);

  if (result_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return result_status;
  }

  // TODO: should return error when longer than entered
  char gid_as_string[256];
  snprintf(gid_as_string, 255, "%d", group_result->gr_gid);
  enum nss_status group_members_status = maria_query_with_param(
    "_nss_maria_getgrnam_r",
    settings->memsbygid,
    gid_as_string,
    settings,
    &conn,
    &group_members_result,
    errnop
  );

  if (group_members_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return group_members_status;
  }

  enum nss_status group_members_copy_status = copy_group_members_to_group(group_members_result, group_result, buffer, buflen, &occupied_buffer, errnop);

  free(settings);
  mysql_free_result(group_members_result);
  mysql_free_result(result);
  mysql_close(conn);
  return group_members_copy_status;
}

enum nss_status _nss_maria_getgrgid_r (
  uid_t gid,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrgid_r called!");

  // TODO: should return error when longer than entered
  char gid_as_string[256];
  snprintf(gid_as_string, 255, "%d", gid);

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_RES *group_members_result;
  MYSQL_ROW row;
  size_t occupied_buffer = 0;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_getgrgid_r",
    settings->getgrgid,
    gid_as_string,
    settings,
    &conn,
    &result,
    errnop
  );

  if (status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return status;
  }

  enum nss_status row_status = maria_get_row(&conn, &result, &row, errnop);

  if (row_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return row_status;
  }

  enum nss_status result_status = copy_db_row_to_group(row, group_result, buffer, buflen, &occupied_buffer, errnop);

  if (result_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return result_status;
  }

  enum nss_status group_members_status = maria_query_with_param(
    "_nss_maria_getgrnam_r",
    settings->memsbygid,
    gid_as_string,
    settings,
    &conn,
    &group_members_result,
    errnop
  );

  if (group_members_status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return group_members_status;
  }

  enum nss_status group_members_copy_status = copy_group_members_to_group(group_members_result, group_result, buffer, buflen, &occupied_buffer, errnop);

  free(settings);
  mysql_free_result(group_members_result);
  mysql_free_result(result);
  mysql_close(conn);
  return group_members_copy_status;
}

enum nss_status _nss_maria_initgroups_dyn (
  const char *username,
  gid_t gid,
  long int *start_index,
  long int *gids_size,
  gid_t **gids,
  long int limit,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_initgroups_dyn called!");

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    *errnop = ENOENT;
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL *conn;
  MYSQL_RES *result;

  enum nss_status status = maria_query_with_param(
    "_nss_maria_initgroups_dyn",
    settings->gidsbymem,
    username,
    settings,
    &conn,
    &result,
    errnop
  );

  if (status != NSS_STATUS_SUCCESS) {
    free(settings);
    mysql_free_result(result);
    mysql_close(conn);
    return status;
  }

  enum nss_status gids_copy_status = copy_gids(result, start_index, gids_size, gids, limit, errnop);

  free(settings);
  mysql_free_result(result);
  mysql_close(conn);
  return gids_copy_status;
}

enum nss_status _nss_maria_getgrent_r (
  struct group *group_result,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getgrent_r called!");

  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  enum nss_status row_status;
  enum nss_status copy_status;
  enum nss_status members_status;
  enum nss_status members_copy_status;
  MYSQL_RES *group_members_result;
  MYSQL_ROW row;
  size_t occupied_buffer = 0;

  if((row_status = maria_get_row(&group_dbconn, &group_dbresult, &row, errnop)) != NSS_STATUS_SUCCESS) {
    return row_status;
  }

  if((copy_status = copy_db_row_to_group(row, group_result, buffer, buflen, &occupied_buffer, errnop)) != NSS_STATUS_SUCCESS) {
    return copy_status;
  }

  // TODO: should return error when longer than entered
  char gid_as_string[256];
  snprintf(gid_as_string, 255, "%d", group_result->gr_gid);

  if((members_status = maria_query_with_param(
    "_nss_maria_getgrnam_r",
    settings->memsbygid,
    gid_as_string,
    settings,
    &group_dbconn,
    &group_members_result,
    errnop
  )) != NSS_STATUS_SUCCESS) {
    return members_status;
  }

  if((members_copy_status = copy_group_members_to_group(
    group_members_result,
    group_result,
    buffer,
    buflen,
    &occupied_buffer,
    errnop
  )) != NSS_STATUS_SUCCESS) {
    return members_copy_status;
  }

  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_maria_setgrent (void) {
  debug_print("_nss_maria_setgrent called!");

  int err;
  Maria_config *settings = malloc(sizeof(*settings));
  if(maria_read_config_file(settings, "/etc/libnss-maria.conf") > 0) {
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  enum nss_status status = maria_query_no_param(
    "_nss_maria_setspent",
    settings->getgrent,
    settings,
    &group_dbconn,
    &group_dbresult,
    &err
  );

  free(settings);
  return status;
}

enum nss_status _nss_maria_endgrent (void) {
  debug_print("_nss_maria_endgrent called!");

  mysql_free_result(group_dbresult);
  mysql_close(group_dbconn);
  return NSS_STATUS_SUCCESS;
}
