#ifndef MARIA_LOGGER_H
#define MARIA_LOGGER_H
#include <syslog.h>
#include <stdarg.h>

void maria_log(const char *message, ...);

#ifdef NDEBUG
  #define debug_print maria_log("debug disabled");
#else
  #define debug_print(msg) \
    do { \
      fprintf( \
        stderr, \
        "%s:%d:%s(): " msg "\n", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
    } while (0); \
    do { \
      char message[1024] = ""; \
      sprintf(message, \
        "%s:%d:%s(): " msg "\n", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
      maria_log(message); \
    } while (0);
#endif

#endif
