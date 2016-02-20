include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(libnss_maria_config_test libnss_maria_config_test.c)
#add_executable(libnss_maria_db_test libnss_maria_test.c)

# m = math, z = zlib
target_link_libraries(libnss_maria_config_test nss-maria crypto ssl dl pthread m z config mysqlclient_r)

add_test(config_test libnss_maria_config_test)
