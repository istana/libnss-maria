#!/bin/sh
docker-compose exec sys sh -c "CONFIG_FILE=\"libnss-maria-docker.conf\" /home/libnss-maria/scripts/compile_and_test.sh"
