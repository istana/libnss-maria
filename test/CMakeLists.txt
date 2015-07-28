include_directories("${CMAKE_SOURCE_DIR}/src")
add_executable(nss-maria-test nss-maria-test.c)
target_link_libraries(nss-maria-test nss-maria mysqlclient_r)

## Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions (--std=c99 -Wall -Wextra -Werror)
endif()

