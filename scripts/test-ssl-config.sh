#!/bin/sh
docker-compose -f docker-compose-unix-socket.yml exec sys \
sh -c "CLIENT_FILE=\"ssl/client.cnf\" CONFIG_FILE=\"ssl/libnss-maria.conf\" TEST_USE_SSL=\"1\" /home/libnss-maria/scripts/compile_and_test.sh"
