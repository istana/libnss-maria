#!/bin/sh

function dostuff {
  docker exec -it libnss-maria_sys_1 sh -c "$1"
}

REAL_PATH=`realpath -e -m $0`
SCRIPTS_DIR=`dirname $REAL_PATH`

echo SCRIPTS $SCRIPTS_DIR
DEBUG_BUILD=${SCRIPTS_DIR}/../Debug

rm -rf $DEBUG_BUILD
mkdir $DEBUG_BUILD
sleep 1

docker exec -it libnss-maria_build_1 sh -c 'cd /home/libnss-maria/Debug && cmake -D CMAKE_BUILD_TYPE=Debug .. && make && ctest --verbose'

# go to scripts directory, ugly, but well..
cd $SCRIPTS_DIR

dostuff 'cp /home/libnss-maria/Debug/src/libnss-maria.so.2.1.0 /usr/lib/x86_64-linux-gnu/libnss_maria.so'
dostuff 'cp /home/libnss-maria/Debug/src/libnss-maria.so.2.1.0 /usr/lib/libnss_maria.so.2'
dostuff 'cp /home/libnss-maria/Debug/src/libnss-maria.so.2.1.0 /usr/lib/libnss_maria.so.2.0.0'
dostuff 'cp /home/libnss-maria/Debug/src/libnss-maria.so.2.1.0 /usr/lib/libnss_maria.so.2.1.0'

dostuff 'cp /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc'
dostuff 'cp /home/libnss-maria/examples/sos-sso/libnss-maria.conf /etc'
dostuff 'cp /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc'

dostuff 'getent passwd katarina || echo "No user found"'
