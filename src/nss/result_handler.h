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
#include <mysql.h>

enum nss_status copy_db_row_to_passwd(MYSQL_ROW row, struct passwd *passwd_result, char *buffer, size_t buflen, int *errnop);
enum nss_status copy_db_row_to_shadow(MYSQL_ROW row, struct spwd *shadow_result, char *buffer, size_t buflen, int *errnop);

#endif
