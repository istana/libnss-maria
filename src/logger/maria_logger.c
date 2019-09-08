#include <stdio.h>
#include "maria_logger.h"

void maria_log(const char *message, ...) {
  openlog("libnss-maria", LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "%s", message);
  closelog();

  //FILE *logfile = fopen("/etc/maria_log.txt", "a");
  //fprintf(logfile, "%s\n", message);

  va_list ap;
  va_start(ap, message);
  vfprintf(stderr, message, ap);
  va_end(ap);
  fflush(stderr);
}
