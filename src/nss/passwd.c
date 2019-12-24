#define STRING_SIZE 255
#include "./passwd.h"

/*
MYSQL mariadb_connect(Maria_config settings) {
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

  if (real_connection == NULL) {
    maria_log("cannot connect to the database");
  }

  return real_connection;
}

void maria_db_disconnect(MYSQL *connection) {
  mysql_close(connection);
}
*/

// shouldn't use malloc at all, but put everything from passwd into *buffer variable
enum nss_status _nss_maria_getpwnam_r (
  const char *name,
  struct passwd *result_buf,
  char *buffer,
  size_t buflen,
  int *errnop,
  int *h_errnop
) {
  debug_print("_nss_maria_getpwnam_r called!");
  Maria_config *settings = malloc(sizeof(*settings));
  maria_read_config_file(settings, "/etc/libnss-maria.conf");
  debug_print_var("_nss_maria_getpwnam_r database settings-dbhost:%s;dbname:%s;\
dbuser:%s;dbpass:%s;dbport:%lld;getpwnam_query:%s",
    settings->dbhost,
    settings->dbname,
    settings->dbuser,
    settings->dbpass,
    settings->dbport,
    settings->getpwnam
  );

  const char *placeholder = memchr(settings->getpwnam, '?', strlen(settings->getpwnam));

  if(!placeholder) {
    debug_print("_nss_maria_getpwnam_r placeholder not found in database query");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  const char *query = "SELECT username FROM users";

  MYSQL *conn = mysql_init(NULL);
  if(!conn) {
    debug_print("mysql init failed, out of memory");
    return NSS_STATUS_UNAVAIL;
  }

  if(mysql_real_connect(
    conn,
    settings->dbhost,
    settings->dbuser,
    settings->dbpass,
    settings->dbname,
    settings->dbport,
    NULL,
    0
  ) == NULL) {
    debug_print("_nss_maria_getpwnam_r cannot connect to the database");

    free(settings);
    return NSS_STATUS_TRYAGAIN;
  }

  char *name_sanitized = malloc((sizeof(char) * strlen(name) * 2) + 1);
  mysql_real_escape_string(conn, name_sanitized, name, strlen(name));
  char *final_query = str_replace(settings->getpwnam, "?", name_sanitized);
  debug_print_var(final_query);

  if (mysql_real_query(conn, final_query, strlen(final_query)) != 0) {
    debug_print("_nss_maria_getpwnam_r cannot execute getpwnam mariadb query");
    log_mysql_error(conn);
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_RES *result = mysql_store_result(conn);

  if(result == NULL) {
    debug_print("_nss_maria_getpwnam_r cannot get result from query");
    free(settings);
    return NSS_STATUS_UNAVAIL;
  }

  MYSQL_ROW row = mysql_fetch_row(result);

  if (row == NULL) {
    debug_print("_nss_maria_getpwnam_r no result found");
    free(settings);
    mysql_free_result(result);
    return NSS_STATUS_NOTFOUND;
  }

  debug_print("wohoohooo");

  char *xname = malloc(sizeof(char) * 256);
  char *password = malloc(sizeof(char) * 256);
  char *gecos = malloc(sizeof(char) * 256);
  char *homedir = malloc(sizeof(char) * 256);
  char *shell = malloc(sizeof(char) * 256);

  strncpy(xname, row[0], 255);
  strncpy(password, row[1], 255);
  strncpy(gecos, row[4], 255);
  strncpy(homedir, row[5], 255);
  strncpy(shell, row[6], 255);

  result_buf->pw_name = xname;
  result_buf->pw_passwd = password;
  result_buf->pw_uid = strtoul(row[2], NULL, 10);
  result_buf->pw_gid = strtoul(row[3], NULL, 10);
  result_buf->pw_gecos = gecos;
  result_buf->pw_dir = homedir;
  result_buf->pw_shell = shell;

  free(settings);
  mysql_free_result(result);
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