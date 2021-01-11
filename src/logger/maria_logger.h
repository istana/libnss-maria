#ifndef MARIA_LOGGER_H
#define MARIA_LOGGER_H
#include <syslog.h>
#include <stdarg.h>
#include <stdio.h>

void maria_log(const char *message, ...);

#ifdef VERBOSE
  #define debug_print(msg) \
    do { \
      char xmessage[4096] = ""; \
      sprintf(xmessage, \
        "%s:%d:%s(): " msg "\n", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
      maria_log(xmessage); \
    } while (0);
#else
  #define debug_print(msg)
#endif

#ifdef VERBOSE
  #define debug_print_var(...) \
    do { \
      char xmessage[4096] = ""; \
      snprintf(xmessage, \
        sizeof(xmessage), \
        "%s:%d:%s(): ", \
        __FILE__, \
        __LINE__, \
        __func__ \
      ); \
      maria_log(xmessage); \
      maria_log(__VA_ARGS__); \
      maria_log("\n"); \
    } while (0);
#else
  #define debug_print_var(...)
#endif

#define log_mysql_error(mysql_handle) \
  maria_log("server information: %s\n", mysql_get_server_info(mysql_handle));\
  maria_log("error number: %u, error: %s\n", mysql_errno(mysql_handle), mysql_error(mysql_handle));

#define log_mysql_stmt_error(mysql, stmt) \
  maria_log("server information: %s\n", mysql_get_server_info(mysql));\
  maria_log("error number: %u, error: %s\n", mysql_errno(mysql), mysql_error(mysql));\
  maria_log("error number: %u, error: %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
#endif
