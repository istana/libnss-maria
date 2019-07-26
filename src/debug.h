#include <string.h>
#include <stdio.h>
#include "./logger/maria_logger.h"

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