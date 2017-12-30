#!/bin/bash

CONTAINER_NAME=libnssmaria_sys_1
DB_CONTAINER=libnssmaria_database_1

function run_docker {
	docker exec -it ${CONTAINER_NAME} $1
}

function run_database {
  docker exec -it ${DB_CONTAINER} sh -c "echo $1 | mysql -u root"
}

docker-compose down
docker-compose build && docker-compose up -d

# TODO: choose correct name
#docker cp Debug/src/libnss-maria.so.2 ${CONTAINER_NAME}:/usr/lib/libnss_mysql.so.2.0.0
#docker cp Debug/src/libnss-maria.so.2 ${CONTAINER_NAME}:/usr/lib/libnss_mysql.so.2.1.0
#docker cp Debug/src/libnss-maria.so.2 ${CONTAINER_NAME}:/usr/lib/libnss_mysql.so.2

docker cp examples/sos-sso/libnss-maria.conf ${CONTAINER_NAME}:/etc
docker cp examples/sos-sso/libnss-maria-root.conf ${CONTAINER_NAME}:/etc
docker cp examples/sos-sso/nsswitch.conf ${CONTAINER_NAME}:/etc

run_database "CREATE DATABASE sos-sso"

run_docker "getent passwd root"
run_docker "getent passwd testuser"
RETURNCODE=$?

#docker-compose down

if [ "$RETURNCODE" -gt 0 ]; then
  echo "TEST FAIL"
else
  echo "TEST SUCCESS"
fi

exit $RETURNCODE;
