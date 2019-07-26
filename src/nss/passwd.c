#define STRING_SIZE 255
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include "passwd.h"
#include "../debug.h"
#include "../configuration/maria_config.h"

/*
MYSQL maria_db_connect(Maria_config settings) {
  MYSQL *connection = mysql_init(NULL);
  MYSQL real_connection = mysql_real_connect(
    connection,
    settings.dbhost,
    settings.dbuser,
    settings.dbpass,
    settings.dbname,
    settings.dbport,
    "",
    0
  );

  if (!real_connection) {
    print_debug("cannot connect to the database");
  }

  return real_connection;
}
*/
void maria_db_disconnect(MYSQL *connection) {
  mysql_close(connection);
}


// shouldn't use malloc at all, but put everything from passwd into *buffer variable
enum nss_status _nss_maria_getpwnam_r (
  const char *name_query,
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getpwnam_r called!");

/*
  my_bool result_is_null[7];
  my_bool result_error[7];
  unsigned long length[7];
  char name_buf[STRING_SIZE];
  char passwd_buf[STRING_SIZE];
  unsigned long uid_buf[STRING_SIZE];
  unsigned long gid_buf;
  char gecos_buf;
  char dir_buf[STRING_SIZE];
  char shell_buf[STRING_SIZE];

  char *name = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);
  char *gecos = malloc(sizeof(char) * 256);
  char *dir = malloc(sizeof(char) * 256);
  char *shell = malloc(sizeof(char) * 256);
*/
/*
  Maria_config settings = maria_read_config_file("/etc/libnss-maria.conf");
  MYSQL *conn = maria_db_connect(settings);
  MYSQL_STMT *statement = mysql_stmt_init(conn);
  MYSQL_STMT *stmt = mysql_stmt_prepare(query, settings.getpwnam, strlen(settings.getpwnam));
*/
/*
  MYSQL_BIND bind_params[1];
  memset(bind_params, 0, sizeof(bind_params));
  bind_params[0].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_params[0].buffer = name_query;
  bind_params[0].buffer_length = strlen(name_query);

  mysql_stmt_bind_result(stmt, bind);

  // no wonder ActiveRecord from Rails doesn't use prepared statements
  MYSQL_BIND bind_result[7];
  memset(bind_result, 0, sizeof(bind_result) * 7);
  bind_result[0].buffer_type = MYSQL_TYPE_STRING;
  bind_result[0].buffer = (char *)str_data;
  bind_result[0].buffer_length = STRING_SIZE;
  bind_result[0].is_null = &is_null[0];
  bind_result[0].length = &length[0];
  bind_result[0].error = &error[0];

  bind_result[1].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[1].buffer = name_query;
  bind_result[1].buffer_length = strlen(name_query);
  bind_result[2].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[2].buffer = name_query;
  bind_result[2].buffer_length = strlen(name_query);
  bind_result[3].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[3].buffer = name_query;
  bind_result[3].buffer_length = strlen(name_query);
  bind_result[4].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[4].buffer = name_query;
  bind_result[4].buffer_length = strlen(name_query);
  bind_result[5].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[5].buffer = name_query;
  bind_result[5].buffer_length = strlen(name_query);
  bind_result[6].buffer_type = MYSQL_TYPE_VARCHAR;
  bind_result[6].buffer = name_query;
  bind_result[6].buffer_length = strlen(name_query);
  mysql_stmt_bind_param(prepared_statement, bind);
  //mysql_stmt_store_result(prepared_statement);

  MYSQL_BIND bind;

  mysql_stmt_bind_result(prepared_statement, result)
  mysql_stmt_fetch(prepared_statement);

  mysql_stmt_close(query);


  strncpy(name, "testuser", 255);
  strncpy(password, "x", 255);
  strncpy(gecos, "Unprivileged User Name,", 255);
  strncpy(dir, "/var/empty,", 255);
  strncpy(shell, "/usr/bin/false", 255);


  clear_pw_buffer(result_buf)
  result_buf->pw_name = name;
  result_buf->pw_passwd = password;
  result_buf->pw_uid = 12345;
  result_buf->pw_gid = 6789;
  result_buf->pw_gecos = gecos;
  result_buf->pw_dir = dir;
  result_buf->pw_shell = shell;
*/
  return NSS_STATUS_SUCCESS;
}
/*
enum nss_status _nss_maria_getpwuid_r (
  uid_t uid,
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  char *name = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);
  char *gecos = malloc(sizeof(char) * 256);
  char *dir = malloc(sizeof(char) * 256);
  char *shell = malloc(sizeof(char) * 256);

  strncpy(name, "testuser", 255);
  strncpy(password, "x", 255);
  strncpy(gecos, "Unprivileged User UID,", 255);
  strncpy(dir, "/var/empty,", 255);
  strncpy(shell, "/usr/bin/false", 255);

  result_buf->pw_name = name;
  result_buf->pw_passwd = password;
  result_buf->pw_uid = 12345;
  result_buf->pw_gid = 6789;
  result_buf->pw_gecos = gecos;
  result_buf->pw_dir = dir;
  result_buf->pw_shell = shell;

  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_maria_getpwent_r (
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop
) {
  int value = 9000;

  pthread_key_create(&last_uid, NULL);
  pthread_setspecific(last_uid, &value);

  FILE *logfile;
  logfile = fopen ("/var/log/maria.log", "a+");
  fprintf(
    logfile,
    "_nss_maria_getpwent_r name:%s password:%s gecos:%s dir:%s shell:%s buffer:%s buflen:%lu",
    result_buf->pw_name,
    result_buf->pw_passwd,
    result_buf->pw_gecos,
    result_buf->pw_dir,
    result_buf->pw_shell,
    buffer,
    buflen    
  );

  fclose(logfile);

  char msg[1024];
  sprintf(
    msg,
    "_nss_maria_getpwent_r name:%s password:%s gecos:%s dir:%s shell:%s buffer:%s buflen:%lu",
    result_buf->pw_name,
    result_buf->pw_passwd,
    result_buf->pw_gecos,
    result_buf->pw_dir,
    result_buf->pw_shell,
    buffer,
    buflen    
  );
  maria_log(msg);

  int thread_value = *((long int *) pthread_getspecific(last_uid));
  char msg2[1024];
  sprintf(msg2, "last_uid: %i", thread_value);
  maria_log(msg2);

  if (result_buf->pw_uid > 0) {
    return NSS_STATUS_NOTFOUND;
  }

  char *name = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);
  char *gecos = malloc(sizeof(char) * 256);
  char *dir = malloc(sizeof(char) * 256);
  char *shell = malloc(sizeof(char) * 256);

  strncpy(buffer, "testuser", 255);
  strncpy(buffer+9, "x", 255);
  strncpy(gecos, "Unprivileged User UID,", 255);
  strncpy(dir, "/var/empty,", 255);
  strncpy(shell, "/usr/bin/false", 255);

  result_buf->pw_name = buffer;
  result_buf->pw_passwd = buffer+9;
  result_buf->pw_uid = 12345;
  result_buf->pw_gid = 6789;
  result_buf->pw_gecos = gecos;
  result_buf->pw_dir = dir;
  result_buf->pw_shell = shell;

  return NSS_STATUS_SUCCESS;
}

// closes the database
// but database queries don't use persistent connections
// so empty for now
// is used from getpwent?
enum nss_status _nss_maria_endpwent (void) {
  return NSS_STATUS_SUCCESS;
}

// rewinds the database, how???
// is used from getpwent
enum nss_status _nss_maria_setpwent (void) {
  return NSS_STATUS_SUCCESS;
}
*/