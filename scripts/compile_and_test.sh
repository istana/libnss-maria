#!/bin/bash
if [[ -z $HOME_PATH ]]; then
  HOME_PATH="/home/libnss-maria"
fi

if [[ -z $RELEASE ]]; then
  TARGET="Debug"
else
  TARGET="Release"
fi

SUDO_COMMAND=$([[ -z $TEST_USE_SUDO || $TEST_USE_SUDO = "0" ]] && echo "" || echo "sudo")
CONFIG_FILE=${CONFIG_FILE:-sos-sso/libnss-maria.conf}
CONFIG_ROOT_FILE=${CONFIG_ROOT_FILE:-sos-sso/libnss-maria-root.conf}
SSL_COMMAND=$([[ -z $TEST_USE_SSL || $TEST_USE_SSL = "0" ]] && echo "" || echo "--ssl")

echo "CLIENT_FILE: $CLIENT_FILE"
echo "COMPILE_ONLY: $COMPILE_ONLY"
echo "CONFIG_FILE: $CONFIG_FILE"
echo "CONFIG_ROOT_FILE: $CONFIG_ROOT_FILE"
echo "DC_FILE: $DC_FILE"
echo "DOCKER: $DOCKER"
echo "PREDEFINED_DB: $PREDEFINED_DB"
echo "SSL_COMMAND: $SSL_COMMAND"
echo "SUDO_COMMAND: $SUDO_COMMAND"

rm -rf "$HOME_PATH/$TARGET"
mkdir "$HOME_PATH/$TARGET"

cd ${HOME_PATH}/${TARGET} && cmake -D CMAKE_BUILD_TYPE=${TARGET} .. && make && ctest --verbose
ORIG_RETURN_CODE=$?

if [[ $ORIG_RETURN_CODE -eq 0 && -z $COMPILE_ONLY ]]; then
  $SUDO_COMMAND rm /lib/libnss_maria.so*
  $SUDO_COMMAND cp -bf /home/libnss-maria/${TARGET}/src/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2.0.0 &&
  $SUDO_COMMAND ln -fs /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so &&
  $SUDO_COMMAND ln -fs /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2
  # for fedora, arch linux has the same /lib and /lib64
  if [[ ! -f "/lib64/libnss_maria.so.2" ]]; then
    $SUDO_COMMAND ln -fs /lib/libnss_maria.so.2.0.0 /lib64/libnss_maria.so.2
  fi
  if [[ ! -f "/lib64/libnss_maria.so.2.0.0" ]]; then
    $SUDO_COMMAND ln -fs /lib/libnss_maria.so.2.0.0 /lib64/libnss_maria.so.2.0.0
  fi
  $SUDO_COMMAND chmod 644 /lib/libnss_maria.so.2.0.0 &&

  $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc &&
  $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$CONFIG_FILE /etc/libnss-maria.conf &&
  $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$CONFIG_ROOT_FILE /etc/libnss-maria-root.conf
  if [[ ! -z $CLIENT_FILE ]]; then
    $SUDO_COMMAND cp -bf /home/libnss-maria/examples/$CLIENT_FILE /etc/libnss-maria-client.cnf
  fi
  $SUDO_COMMAND chmod 644 /etc/nsswitch.conf /etc/libnss-maria.conf
  $SUDO_COMMAND chmod 600 /etc/libnss-maria-root.conf

  SSL_COMMAND=$SSL_COMMAND ${HOME_PATH}/test/integration/nss_module.bats
  SSL_COMMAND=$SSL_COMMAND ${HOME_PATH}/test/integration/buffers_test.bats
else
  exit $ORIG_RETURN_CODE
fi
