cmake_minimum_required (VERSION 3.0)
project (nss-maria)

if (CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(COMMON_FLAGS "\
-pipe -pedantic -Wall -Wextra -Wshadow -Wno-missing-field-initializers \
-Wno-unused-parameter -Wold-style-definition -Wdeclaration-after-statement \
-Wmissing-declarations \
-Wmissing-prototypes -Wstrict-prototypes -Wredundant-decls -Wmissing-noreturn \
-Wpointer-arith \
-Wcast-align -Wwrite-strings -Winline -Wformat-nonliteral -Wformat-security \
-Wswitch-enum \
-Winit-self -Wmissing-include-dirs -Wundef -Waggregate-return -Wnested-externs \
-Wunsafe-loop-optimizations -Winvalid-pch -Wcast-qual\
")

  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -pedantic -Wall -Wextra --std=c11 -g -ggdb -O0")
  set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${CMAKE_C_FLAGS_RELEASE} --std=c11 -O3")
endif()

# in addition more options for Clang
# but who compiles stuff for glibc in Clang? :-O
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CLANG_COMMON "-Wall -Wextra -Wmost -Weverything")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CLANG_COMMON}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CLANG_COMMON}")
endif()

message("CMAKE_C_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
message("CMAKE_C_FLAGS_RELEASE is ${CMAKE_C_FLAGS_RELEASE}")

add_subdirectory(src)
add_subdirectory(test)

# this needs to be here and not in test/CMakeLists.txt
enable_testing()
add_test(config_helpers_test test/maria_config_helpers_test)
add_test(config_test test/maria_config_test)
add_test(logger_test test/maria_logger_test)
#add_test(integration_nss_test test/integration/nss_module)
