cmake_minimum_required (VERSION 2.8)
project (nss-maria)

## Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_COMMON "-pipe -pedantic -Wall -Wextra -Wshadow -Wno-missing-field-initializers
    -Wno-unused-parameter -Wold-style-definition -Wdeclaration-after-statement -Wmissing-declarations
    -Wmissing-prototypes -Wstrict-prototypes -Wredundant-decls -Wmissing-noreturn -Wpointer-arith
    -Wcast-align -Wwrite-strings -Winline -Wformat-nonliteral -Wformat-security -Wswitch-enum
    -Winit-self -Wmissing-include-dirs -Wundef -Waggregate-return -Wnested-externs
    -Wunsafe-loop-optimizations -Winvalid-pch -Wcast-qual
  ")

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c99 -g -ggdb -O0 ${CMAKE_CXX_FLAGS_COMMON}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --std=c99 -Werror -O3 ${CMAKE_CXX_FLAGS_COMMON}")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS_CLANG "-Wall -Wextra -Wmost -Weverything")

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_CLANG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS_CLANG}")
endif()

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

add_subdirectory(src)
#add_subdirectory(test)

# this needs to be here and not in test/CMakeLists.txt
#enable_testing()
#add_test(config_helpers_test test/maria_config_helpers_test)
#add_test(config_test test/maria_config_test)
#add_test(logger_test test/maria_logger_test)
#add_test(integration_nss_test test/integration/nss_module)
