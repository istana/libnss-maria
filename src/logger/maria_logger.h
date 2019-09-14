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
      char message[4096] = ""; \
      sprintf(message, \
        "%s:%d:%s(): " msg "\n", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
      maria_log(message); \
    } while (0);
#endif

#ifdef NDEBUG
  #define debug_print_var maria_log("debug disabled");
#else
  #define debug_print_var(...) \
    do { \
      char message[4096] = ""; \
      snprintf(message, \
        sizeof(message), \
        "%s:%d:%s(): ", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
      maria_log(message); \
      maria_log(__VA_ARGS__); \
      maria_log("\n"); \
    } while (0);
#endif

#define log_mysql_error(mysql_handle) \
  maria_log("server information: %s\n", mysql_get_server_info(mysql_handle));\
  maria_log("error number: %u, error: %s\n", mysql_errno(mysql_handle), mysql_error(mysql_handle));

#endif
