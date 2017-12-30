#!/bin/bash

docker-compose build && docker-compose up

docker -it sys_1 getent passwd testuser
