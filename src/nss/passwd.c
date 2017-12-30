#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "passwd.h"
#include "../logger/maria_logger.h"

pthread_key_t last_uid;
//thread_local long long int last_uid = -1;

// shouldn't use malloc at all, but put everything from passwd into *buffer variable
enum nss_status _nss_maria_getpwnam_r (
  const char *name_query,
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
  strncpy(gecos, "Unprivileged User Name,", 255);
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
