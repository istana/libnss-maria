#!/bin/bash

docker-compose down
docker-compose build && docker-compose up -d
docker-compose down

#docker -it sys_1 getent passwd testuser
