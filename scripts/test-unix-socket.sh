#!/bin/sh
docker-compose -f docker-compose-unix-socket.yml exec sys sh -c "CONFIG_FILE=\"libnss-maria.unix_socket.conf\" /home/libnss-maria/scripts/compile_and_test.sh"
