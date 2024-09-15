#!/bin/sh
docker compose -f docker compose-unix-socket.yml exec sys \
sh -c "CLIENT_FILE=\"client.cnf\" CONFIG_FILE=\"libnss-maria.conf\" EXAMPLE_SET=\"ssl\" TEST_USE_SSL=\"1\" /home/libnss-maria/scripts/compile_and_test.sh"
