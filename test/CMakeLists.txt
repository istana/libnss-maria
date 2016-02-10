include_directories("${CMAKE_SOURCE_DIR}/src")
add_executable(nss-maria-test nss-maria-test.c)
# m = math, z = zlib
target_link_libraries(nss-maria-test nss-maria crypto ssl dl pthread m z mysqlclient_r)

## Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c99 -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --std=c99 -Wall -Wextra -Werror")
endif()

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")