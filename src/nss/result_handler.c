#include "result_handler.h"

enum nss_status copy_db_row_to_passwd(MYSQL_ROW row, struct passwd *passwd_result, char *buffer, size_t buflen, int *errnop) {
  size_t username_l = strlen(row[0]);
  size_t password_l = strlen(row[1]);
  size_t gecos_l = strlen(row[4]);
  size_t homedir_l = strlen(row[5]);
  size_t shell_l = strlen(row[6]);

  if (username_l + password_l + gecos_l + homedir_l + shell_l + 5 > buflen) {
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

enum nss_status copy_db_row_to_shadow(MYSQL_ROW row, struct spwd *shadow_result, char *buffer, size_t buflen, int *errnop) {
  size_t username_l = strlen(row[0]);
  size_t password_l = strlen(row[1]);

  if (username_l + password_l + 2 > buflen) {
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
