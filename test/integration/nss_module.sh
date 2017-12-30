#!/bin/bash

docker-compose down
docker-compose build && docker-compose up -d

docker exec -it libnssmaria_sys_1 getent passwd root
docker exec -it libnssmaria_sys_1 getent passwd testuser
RETURNCODE=$?

docker-compose down

if [ "$RETURNCODE" -gt 0 ]; then
  echo "TEST FAIL"
else
  echo "TEST SUCCESS"
fi

exit $RETURNCODE;
