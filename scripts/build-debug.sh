#!/bin/sh

if ! [ -x "$(command -v realpath)" ]; then
  echo 'Error: realpath is not installed or not executable. Install it with coreutils package.' >&2
  exit 1
fi

REAL_PATH=`realpath -e -m $0`
SCRIPTS_DIR=`dirname $REAL_PATH`

echo SCRIPTS $SCRIPTS_DIR
DEBUG_BUILD=${SCRIPTS_DIR}/../Debug

rm -rf $DEBUG_BUILD
mkdir $DEBUG_BUILD
cd $DEBUG_BUILD
cmake -D CMAKE_BUILD_TYPE=Debug ..
make && ctest --verbose

# go to scripts directory, ugly, but well..
cd $SCRIPTS_DIR
