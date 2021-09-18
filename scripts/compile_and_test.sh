#!/bin/bash
set -e

if [[ -z $HOME_PATH ]]; then
  HOME_PATH="/home/libnss-maria"
fi

if [[ -z $RELEASE ]]; then
  TARGET="Debug"
else
  TARGET="Release"
fi

SUDO_COMMAND=$([[ -z $TEST_USE_SUDO || $TEST_USE_SUDO = "0" ]] && echo "" || echo "sudo")
CONFIG_FILE=${CONFIG_FILE:-libnss-maria.conf}
CONFIG_ROOT_FILE=${CONFIG_ROOT_FILE:-libnss-maria-root.conf}
EXAMPLE_SET=${EXAMPLE_SET:-sos-sso}
SSL_COMMAND=$([[ -z $TEST_USE_SSL || $TEST_USE_SSL = "0" ]] && echo "" || echo "--ssl")

echo "CLIENT_FILE: $CLIENT_FILE"
echo "COMPILE_ONLY: $COMPILE_ONLY"
echo "CONFIG_FILE: $CONFIG_FILE"
echo "CONFIG_ROOT_FILE: $CONFIG_ROOT_FILE"
echo "DC_FILE: $DC_FILE"
echo "DOCKER: $DOCKER"
echo "EXAMPLE_SET: $EXAMPLE_SET"
echo "HOME_DIRECTORY: $HOME_DIRECTORY"
echo "PREDEFINED_DB: $PREDEFINED_DB"
echo "SSL_COMMAND: $SSL_COMMAND"
echo "SUDO_COMMAND: $SUDO_COMMAND"
echo "TARGET: $TARGET"
echo "VERBOSE: $VERBOSE"

rm -rf "$HOME_PATH/$TARGET"
mkdir "$HOME_PATH/$TARGET"

cd ${HOME_PATH}/${TARGET} && cmake -D CMAKE_INSTALL_PREFIX='/' -D CMAKE_BUILD_TYPE=${TARGET} -D VERBOSE=${VERBOSE} .. && make && ctest --verbose
ORIG_RETURN_CODE=$?

if [[ $ORIG_RETURN_CODE -eq 0 && -z $COMPILE_ONLY ]]; then
  $SUDO_COMMAND rm -f /lib/libnss_maria.so*
  $SUDO_COMMAND make install

  # test sos-sso example config or other tests compatible with database structure
  if [[ (! -z $EXAMPLE_SET) && -f /home/libnss-maria/examples/$EXAMPLE_SET/nsswitch.conf ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$EXAMPLE_SET/nsswitch.conf /etc
  else
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc
  fi

  if [[ -f /home/libnss-maria/examples/$EXAMPLE_SET/$CONFIG_FILE ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$EXAMPLE_SET/$CONFIG_FILE /etc/libnss-maria.conf
  else
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/$CONFIG_FILE /etc/libnss-maria.conf
  fi

  if [[ -f /home/libnss-maria/examples/$EXAMPLE_SET/$CONFIG_ROOT_FILE ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$EXAMPLE_SET/$CONFIG_ROOT_FILE /etc/libnss-maria-root.conf
  else
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/$CONFIG_ROOT_FILE /etc/libnss-maria-root.conf
  fi

  if [[ ! -z $CLIENT_FILE ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$EXAMPLE_SET/$CLIENT_FILE /etc/libnss-maria-client.cnf
  fi
  $SUDO_COMMAND chmod 644 /etc/nsswitch.conf /etc/libnss-maria.conf
  $SUDO_COMMAND chmod 600 /etc/libnss-maria-root.conf

  echo 'running test/integration/nss_module.bats'
  SSL_COMMAND=$SSL_COMMAND ${HOME_PATH}/test/integration/nss_module.bats
  echo 'running test/integration/buffers_test.bats'
  SSL_COMMAND=$SSL_COMMAND ${HOME_PATH}/test/integration/buffers_test.bats

  # test libnss-mysql example config
  if [[ $EXAMPLE_SET == "sos-sso" ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/libnss-mysql-linux/nsswitch.conf /etc
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/libnss-mysql-linux/$CONFIG_FILE /etc/libnss-maria.conf
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/libnss-mysql-linux/$CONFIG_ROOT_FILE /etc/libnss-maria-root.conf
    $SUDO_COMMAND chmod 644 /etc/nsswitch.conf /etc/libnss-maria.conf
    $SUDO_COMMAND chmod 600 /etc/libnss-maria-root.conf

    echo 'running test/integration/libnss_mysql.bats'
    SSL_COMMAND=$SSL_COMMAND ${HOME_PATH}/test/integration/libnss_mysql.bats
  fi
else
  exit $ORIG_RETURN_CODE
fi
