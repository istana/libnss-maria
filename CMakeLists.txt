cmake_minimum_required (VERSION 3.0)
project (nss-maria)

# -Wdeclaration-after-statement;
set(ENV{COMPILE_OPTIONS} "\
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

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_compile_options($ENV{COMPILE_OPTIONS} $ENV{DEBUG_OPTIONS})
else()
  add_compile_options($ENV{COMPILE_OPTIONS} $ENV{RELEASE_OPTIONS})
endif()

add_subdirectory(src)
add_subdirectory(test)

# this needs to be here and not in test/CMakeLists.txt
enable_testing()
add_test(config_helpers_test test/maria_config_helpers_test)
add_test(config_test test/maria_config_test)
add_test(logger_test test/maria_logger_test)
#add_test(integration_nss_test test/integration/nss_module)
