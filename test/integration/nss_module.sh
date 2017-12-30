#!/bin/bash

CONTAINER_NAME=libnssmaria_sys_1
DB_CONTAINER=libnssmaria_database_1

function run_docker {
	docker exec -it ${CONTAINER_NAME} bash -c "$1"
	return $?
}

function run_database {
  echo $1;
  #docker exec -it ${DB_CONTAINER} bash -c "echo \"$1\" | mysql -u root"
  echo "$1" | docker exec -i ${DB_CONTAINER} mysql -u root nss
}

#docker-compose down
#docker-compose build &&
docker-compose up -d

docker cp Debug/src/libnss-maria.so.2.1.0 ${CONTAINER_NAME}:/lib/x86_64-linux-gnu/libnss_maria.so.2
docker exec ${CONTAINER_NAME} sh -c 'ln -s /lib/x86_64-linux-gnu/libnss_maria.so.2 /usr/lib/x86_64-linux-gnu/libnss_maria.so'

docker cp examples/sos-sso/libnss-maria.conf ${CONTAINER_NAME}:/etc
docker cp examples/sos-sso/libnss-maria-root.conf ${CONTAINER_NAME}:/etc
docker cp examples/sos-sso/nsswitch.conf ${CONTAINER_NAME}:/etc

run_database "CREATE DATABASE nss"

run_database "CREATE USER 'nss-user'@'localhost' IDENTIFIED BY 'password'"
run_database "GRANT ALL PRIVILEGES ON nss.* TO 'nss-user'@'localhost'"

run_database "CREATE USER 'nss-root'@'localhost' IDENTIFIED BY 'password'"
run_database "GRANT ALL PRIVILEGES ON nss.* TO 'nss-root'@'localhost'"

docker cp examples/sos-sso/sql/2-data-structures.sql ${DB_CONTAINER}:/root
docker exec -i ${DB_CONTAINER} sh -c 'mysql -u root nss < /root/2-data-structures.sql'

run_database "INSERT INTO users (id, username, gid, homedir) VALUES ('8000', 'testuser', '8000', '/home/testuser')"

echo -e "\nSetup done...\n"

run_docker "getent passwd root"

if [ "$?" -gt 0 ]; then
  echo "sanity check: getent passwd root TEST FAIL"
else
  echo "sanity check: getent passwd root TEST SUCCESS"
fi

echo -e "\n"

run_docker "getent passwd testuser"

if [ "$?" -gt 0 ]; then
  echo "getent passwd testuser TEST FAIL"
else
  echo "getent passwd testuser TEST SUCCESS"
fi

echo -e "\n"

run_docker "getent passwd | grep testuser"

if [ "$?" -gt 0 ]; then
  echo "getent passwd | grep testuser TEST FAIL"
else
  echo "getent passwd | grep testuser TEST SUCCESS"
fi

exit 0;

#docker-compose down
