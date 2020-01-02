#include <stdio.h>
#include "maria_logger.h"

void maria_log(const char *message, ...) {
  char assembled_message[4096];
  va_list ap;

  va_start(ap, message);
  vsnprintf(assembled_message, 4096, message, ap);
  va_end(ap);

  openlog("libnss-maria", LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "%s", assembled_message);
  closelog();

#ifndef NDEBUG
  va_start(ap, message);
  vfprintf(stderr, message, ap);
  va_end(ap);
  fflush(stderr);
#endif
}
