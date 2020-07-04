#!/bin/bash
if [[ -z $HOME_PATH ]]; then
  HOME_PATH="/home/libnss-maria"
fi

if [[ -z $RELEASE ]]; then
  TARGET="Debug"
else
  TARGET="Release"
fi

SUDO_COMMAND=$([[ -z $TEST_USE_SUDO ]] && echo "" || echo "sudo")
CONFIG_FILE=${CONFIG_FILE:-libnss-maria.conf}

echo "CONFIG_FILE: $CONFIG_FILE"

rm -rf "$HOME_PATH/$TARGET"
mkdir "$HOME_PATH/$TARGET"

cd ${HOME_PATH}/${TARGET} && cmake -D CMAKE_BUILD_TYPE=${TARGET} .. && make && ctest --verbose

if [[ $? -eq 0 && -z $COMPILE_ONLY ]]; then
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
  $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/$CONFIG_FILE /etc/libnss-maria.conf &&
  $SUDO_COMMAND cp -bf /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc

  ${HOME_PATH}/test/integration/nss_module.bats
fi
