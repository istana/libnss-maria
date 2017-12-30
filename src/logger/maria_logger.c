#include <stdio.h>
#include "maria_logger.h"

void maria_log(const char *message) {
  openlog("libnss-maria", LOG_PID|LOG_CONS, LOG_USER);
  syslog(LOG_INFO, "%s", message);
  closelog();
}
