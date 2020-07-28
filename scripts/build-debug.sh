#!/bin/sh

if ! [ -x "$(command -v realpath)" ]; then
  echo 'Error: realpath is not installed or not executable. Install it with coreutils package.' >&2
  exit 1
fi

REAL_PATH="`realpath -e -m $0`"
SCRIPTS_DIR="`dirname "$REAL_PATH"`"

HOME_PATH="${SCRIPTS_DIR}/.." "${SCRIPTS_DIR}"/compile_and_test.sh
