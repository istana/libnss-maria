cmake_minimum_required (VERSION 3.11)
project (nss_maria)

set(ENV{COMPILE_OPTIONS_SHARED} "\
-pipe;-pedantic;-Wall;-Wextra;-Wshadow;-Wno-missing-field-initializers;\
-Wno-unused-parameter;-Wold-style-definition;\
-Wmissing-declarations;\
-Wmissing-prototypes;-Wstrict-prototypes;-Wredundant-decls;-Wmissing-noreturn;\
-Wpointer-arith;\
-Wcast-align;-Wwrite-strings;-Winline;-Wformat-nonliteral;-Wformat-security;\
-Wswitch-enum;\
-Winit-self;-Wmissing-include-dirs;-Wundef;-Waggregate-return;-Wnested-externs;\
-Wunsafe-loop-optimizations;-Winvalid-pch;-Wcast-qual;\
--std=c11\
")
set(ENV{DEBUG_OPTIONS} "-g;-ggdb;-O0")
set(ENV{RELEASE_OPTIONS} "-O3;-Werror")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options($ENV{COMPILE_OPTIONS_SHARED} $ENV{DEBUG_OPTIONS})

  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER 10)
    add_compile_options("-fanalyzer")
  endif()

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options("-fanalyzer")
  endif()

else()
  add_compile_options($ENV{COMPILE_OPTIONS_SHARED} $ENV{RELEASE_OPTIONS})
endif()

# mega useful to debug compile parameters
# https://cmake.org/cmake/help/latest/variable/CMAKE_DEBUG_TARGET_PROPERTIES.html
#set(CMAKE_DEBUG_TARGET_PROPERTIES COMPILE_OPTIONS)

add_subdirectory(src)
add_subdirectory(test)

# this needs to be here and not in test/CMakeLists.txt
enable_testing()
add_test(config_helpers_test test/maria_config_helpers_test)
add_test(config_test test/maria_config_test)
add_test(logger_test test/maria_logger_test)
# add_test(integration_nss_test test/integration/nss_module)
