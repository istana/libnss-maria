#include "result_handler.h"

enum nss_status copy_db_row_to_passwd(
  MYSQL_RES *passwd_query_result,
  MYSQL_ROW_OFFSET passwd_query_initial_offset,
  MYSQL_ROW row,
  struct passwd *passwd_result,
  char *buffer,
  size_t buflen,
  int *errnop
) {
  size_t username_l = strlen(row[0]);
  size_t password_l = strlen(row[1]);
  size_t gecos_l = strlen(row[4]);
  size_t homedir_l = strlen(row[5]);
  size_t shell_l = strlen(row[6]);

  if (username_l + password_l + gecos_l + homedir_l + shell_l + 5 > buflen) {
    mysql_row_seek(passwd_query_result, passwd_query_initial_offset);
    debug_print("copy_db_row_to_passwd: buffer too small");
    *errnop = ERANGE;
    return NSS_STATUS_TRYAGAIN;
  }

  memset(buffer, 0, buflen);

  char *username_buf = buffer;
  char *password_buf = buffer + username_l + 1;
  char *gecos_buf = password_buf + password_l + 1;
  char *homedir_buf = gecos_buf + gecos_l + 1;
  char *shell_buf = homedir_buf + homedir_l + 1;

  strncpy(username_buf, row[0], username_l);
  strncpy(password_buf, row[1], password_l);
  strncpy(gecos_buf, row[4], gecos_l);
  strncpy(homedir_buf, row[5], homedir_l);
  strncpy(shell_buf, row[6], shell_l);

  passwd_result->pw_name = username_buf;
  passwd_result->pw_passwd = password_buf;
  passwd_result->pw_uid = strtoul(row[2], NULL, 10);
  passwd_result->pw_gid = strtoul(row[3], NULL, 10);
  passwd_result->pw_gecos = gecos_buf;
  passwd_result->pw_dir = homedir_buf;
  passwd_result->pw_shell = shell_buf;

  return NSS_STATUS_SUCCESS;
}

enum nss_status copy_db_row_to_shadow(
  MYSQL_RES *shadow_query_result,
  MYSQL_ROW_OFFSET shadow_query_initial_offset,
  MYSQL_ROW row,
  struct spwd *shadow_result,
  char *buffer,
  size_t buflen,
  int *errnop
) {
  size_t username_l = strlen(row[0]);
  size_t password_l = strlen(row[1]);

  if (username_l + password_l + 2 > buflen) {
    mysql_row_seek(shadow_query_result, shadow_query_initial_offset);
    *errnop = ERANGE;
    return NSS_STATUS_TRYAGAIN;
  }

  memset(buffer, 0, buflen);

  char *username_buf = buffer;
  char *password_buf = buffer + username_l + 1;

  strncpy(username_buf, row[0], username_l);
  strncpy(password_buf, row[1], password_l);

  shadow_result->sp_namp = username_buf;
  shadow_result->sp_pwdp = password_buf;
  shadow_result->sp_lstchg = strtol(row[2], NULL, 10);
  shadow_result->sp_min = strtol(row[3], NULL, 10);
  shadow_result->sp_max = strtol(row[4], NULL, 10);
  shadow_result->sp_warn = strtol(row[5], NULL, 10);
  shadow_result->sp_inact = strtol(row[6], NULL, 10);
  shadow_result->sp_expire = strtol(row[7], NULL, 10);
  shadow_result->sp_flag = strtoul(row[8], NULL, 10);

  return NSS_STATUS_SUCCESS;
}

enum nss_status copy_db_row_to_group(
  MYSQL_RES *group_query_result,
  MYSQL_ROW_OFFSET group_query_initial_offset,
  MYSQL_ROW row,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  size_t *occupied_buffer,
  int *errnop
) {
  size_t groupname_l = strlen(row[0]);
  size_t password_l = strlen(row[1]);

  if (groupname_l + password_l + 2 > buflen) {
    mysql_row_seek(group_query_result, group_query_initial_offset);
    *errnop = ERANGE;
    return NSS_STATUS_TRYAGAIN;
  }

  memset(buffer, 0, buflen);

  char *groupname_buf = buffer;
  char *password_buf = buffer + groupname_l + 1;

  strncpy(groupname_buf, row[0], groupname_l);
  strncpy(password_buf, row[1], password_l);
  *occupied_buffer = groupname_l + password_l + 2;

  group_result->gr_name = groupname_buf;
  group_result->gr_passwd = password_buf;
  group_result->gr_gid = strtoul(row[2], NULL, 10);

  return NSS_STATUS_SUCCESS;
}

enum nss_status copy_group_members_to_group(
  MYSQL_RES *group_query_result,
  MYSQL_ROW_OFFSET group_query_initial_offset,
  MYSQL_RES *members_query_result,
  struct group *group_result,
  char *buffer,
  size_t buflen,
  size_t *occupied_buffer,
  int *errnop
) {
  // buffer: [...occupied, [char* for each member](rows.length+1), [members](rows.length)]
  memset(&(buffer[*occupied_buffer]), 0, buflen - *occupied_buffer);

  my_ulonglong rows_len = mysql_num_rows(members_query_result);
  
  // array of pointers to strings (members)
  char **ptr_array = (char**)&(buffer[*occupied_buffer]);
  int ptr_size = sizeof(char*) * (rows_len + 1);
  
  if (*occupied_buffer + ptr_size > buflen) {
    maria_log("first buffer out of range, buflen: %zu\n", buflen);
    mysql_row_seek(group_query_result, group_query_initial_offset);
    *errnop = ERANGE;
    return NSS_STATUS_TRYAGAIN;
  }

  *occupied_buffer += ptr_size;

  for(my_ulonglong i = 0; i < rows_len; i++) {
    MYSQL_ROW row = mysql_fetch_row(members_query_result);

    if (row == NULL) {
      maria_log("row is null");
      *errnop = EAGAIN;
      return NSS_STATUS_TRYAGAIN;
    }

    char *name = row[0];
    size_t name_l = strlen(name);

    if (*occupied_buffer + name_l + 1 > buflen) {
      debug_print_var("second buffer out of range, buflen: %zu\n", buflen);
      mysql_row_seek(group_query_result, group_query_initial_offset);
      *errnop = ERANGE;
      return NSS_STATUS_TRYAGAIN;
    }

    // TODO: fix warnings
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstringop-truncation"
    #pragma GCC diagnostic ignored "-Wstringop-overflow"
      strncpy(&(buffer[*occupied_buffer]), name, name_l);
    #pragma GCC diagnostic pop
    ptr_array[i] = &(buffer[*occupied_buffer]);
    *occupied_buffer += name_l + 1;
  }

  group_result->gr_mem = (char **)ptr_array;

  return NSS_STATUS_SUCCESS;
}

enum nss_status copy_gids(
  MYSQL_RES *result,
  MYSQL_ROW_OFFSET result_initial_offset,
  long int *start_index,
  long int *gids_size,
  gid_t **gids,
  long int limit,
  int *errnop
) {
  gid_t *group_slots = *gids;
  long int available_gids = *gids_size - *start_index;

  my_ulonglong rows_len = mysql_num_rows(result);
  if (limit > available_gids || (long int)rows_len > available_gids) {
    mysql_row_seek(result, result_initial_offset);
    *errnop = ERANGE;
    return NSS_STATUS_TRYAGAIN;
  }

  for(long int i = *start_index; i < *gids_size; i++) {
    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL) {
      *errnop = EAGAIN;
      return NSS_STATUS_TRYAGAIN;
    }

    group_slots[i] = strtoul(row[0], NULL, 10);
    *start_index += 1;
  }

  return NSS_STATUS_SUCCESS;
}
