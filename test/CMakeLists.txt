cmake_minimum_required (VERSION 2.8)
include_directories("${CMAKE_SOURCE_DIR}/src")

# copy test fixtures to build directory
file(COPY "${CMAKE_SOURCE_DIR}/test/fixtures" DESTINATION ".")
#file(COPY "${CMAKE_SOURCE_DIR}/sample" DESTINATION ".")

# add vendorized "criterion" to path
# cmake --help-policy CMP0015
cmake_policy(SET CMP0015 NEW)
include_directories(vendor/criterion-v2.3.2/include)
link_directories(vendor/criterion-v2.3.2/lib)

add_executable(maria_config_helpers_test "configuration/maria_config_helpers_test.c")
add_executable(maria_logger_test "logger/maria_logger_test.c")
#add_executable(maria_queries_test libnss_maria_queries_test.c)

# m = math, z = zlib
target_link_libraries(maria_config_helpers_test nss-maria config criterion)
target_link_libraries(maria_logger_test nss-maria config criterion)
#target_link_libraries(libnss_maria_queries_test nss-maria crypto ssl dl pthread m z config mariadbclient_r criterion)
