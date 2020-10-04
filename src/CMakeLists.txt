cmake_minimum_required (VERSION 3.11)
set (PROJECT_SOURCE_DIR src)
set (PROJECT_BINARY_DIR src)

# find mariadb or mysql
find_package(PkgConfig REQUIRED)
pkg_search_module(MARMYSQL REQUIRED libmariadb libmysqlclient)

add_library(nss_maria SHARED
  "configuration/maria_config.c"
  "configuration/maria_config_helpers.c"
  "logger/maria_logger.c"
  "nss/passwd.c"
  "nss/group.c"
  "nss/result_handler.c"
  "nss/shadow.c"
  "str_replace.c"
  "mariadb/query.c"
)

# soname (MAJOR) version must be 2 (probably relates to glibc version, i.e. 2.26).
set (nss_maria_VERSION_MAJOR 2)
set (nss_maria_VERSION_MINOR 0)
set (nss_maria_VERSION_PATCH 0)
set(nss_maria_VERSION ${nss_maria_VERSION_MAJOR}.${nss_maria_VERSION_MINOR}.${nss_maria_VERSION_PATCH})
set_target_properties(nss_maria PROPERTIES
  VERSION ${nss_maria_VERSION}
  SOVERSION ${nss_maria_VERSION_MAJOR}
)

if(VERBOSE)
  add_definitions(-DVERBOSE=1)
  set(VERBOSE ON)
endif()


include_directories(SYSTEM ${MARMYSQL_INCLUDE_DIRS})
target_link_libraries(nss_maria config ${MARMYSQL_LDFLAGS})

add_executable(config_db_settings "util/config_db_settings.c")
target_link_libraries(config_db_settings nss_maria config ${MARMYSQL_LDFLAGS})
