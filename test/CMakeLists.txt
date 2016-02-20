include_directories("${CMAKE_SOURCE_DIR}/src")

# copy test fixtures to build directory
file(COPY "${CMAKE_SOURCE_DIR}/test/fixtures" DESTINATION ".")

# add vendorized "criterion" to path
# cmake --help-policy CMP0015
cmake_policy(SET CMP0015 NEW)
include_directories(vendor/criterion-v2.2.0/include)
link_directories(vendor/criterion-v2.2.0/lib)

add_executable(libnss_maria_config_test libnss_maria_config_test.c)
#add_executable(libnss_maria_db_test libnss_maria_test.c)

# m = math, z = zlib
target_link_libraries(libnss_maria_config_test nss-maria crypto ssl dl pthread m z config mysqlclient_r criterion)
