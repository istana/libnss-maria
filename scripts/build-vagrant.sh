#!/bin/sh

if ! [ -x "$(command -v realpath)" ]; then
  echo 'Error: realpath is not installed or not executable. Install it with coreutils package.' >&2
  exit 1
fi

function dostuff {
  vagrant ssh -c "$1"
}

REAL_PATH=`realpath -e -m $0`
SCRIPTS_DIR=`dirname $REAL_PATH`

echo SCRIPTS $SCRIPTS_DIR
DEBUG_BUILD=${SCRIPTS_DIR}/../Debug

rm -rf $DEBUG_BUILD &&
mkdir $DEBUG_BUILD &&
sleep 1

dostuff 'cd /home/libnss-maria/Debug && cmake -D CMAKE_BUILD_TYPE=Debug .. \
&& make && ctest --verbose' &&

# go to scripts directory, ugly, but well..
cd $SCRIPTS_DIR &&

dostuff 'sudo rm /lib/libnss_maria.so*'
dostuff 'sudo cp /home/libnss-maria/Debug/src/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2.0.0' &&
dostuff 'sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so' &&
dostuff 'sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2' &&
dostuff 'sudo chmod 644 /lib/libnss_maria.so.2.0.0' &&

dostuff 'sudo cp /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc' &&
dostuff 'sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria.conf /etc' &&
dostuff 'sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc' &&

dostuff 'getent passwd katarina || echo "No user found"'
