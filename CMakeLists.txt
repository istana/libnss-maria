cmake_minimum_required (VERSION 2.8)
project (nss-maria)

## Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c99 -Wall -Wextra -g")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --std=c99 -Wall -Wextra -Werror")
endif()

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

add_subdirectory(src)
add_subdirectory(test)

# this needs to be here and not in test/CMakeLists.txt
enable_testing()
add_test(config_test test/libnss_maria_config_test)
add_test(queries_test test/libnss_maria_queries_test)
