#!/bin/sh
docker compose -f docker compose-unix-socket.yml exec sys \
sh -c "CONFIG_FILE=\"libnss-maria.conf\" EXAMPLE_SET=\"unix_socket\" /home/libnss-maria/scripts/compile_and_test.sh"
