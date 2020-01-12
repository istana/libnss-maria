#!/bin/bash
if [[ -z $HOME_PATH ]]; then
  HOME_PATH="/home/libnss-maria"
fi

if [[ -z $PRODUCTION ]]; then
  TARGET="Debug"
else
  TARGET="Release"
fi

SUDO_COMMAND=$([[ -z $TEST_USE_SUDO ]] && echo "" || echo "sudo")

rm -rf "$HOME_PATH/$TARGET"
mkdir "$HOME_PATH/$TARGET"

cd ${HOME_PATH}/${TARGET} && cmake -D CMAKE_BUILD_TYPE=${TARGET} .. && make && ctest --verbose

if [[ $? -eq 0 && -z $COMPILE_ONLY ]]; then
  $SUDO_COMMAND rm /lib/libnss_maria.so*
  $SUDO_COMMAND cp /home/libnss-maria/${TARGET}/src/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2.0.0 &&
  $SUDO_COMMAND ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so &&
  $SUDO_COMMAND ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2 &&
  $SUDO_COMMAND chmod 644 /lib/libnss_maria.so.2.0.0 &&

  $SUDO_COMMAND cp /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc &&
  $SUDO_COMMAND cp /home/libnss-maria/examples/sos-sso/libnss-maria.conf /etc &&
  $SUDO_COMMAND cp /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc

  if ! [[ -z $DOCKER ]]; then
    $SUDO_COMMAND cp /home/libnss-maria/examples/sos-sso/libnss-maria-docker.conf /etc/libnss-maria.conf
  fi

  ${HOME_PATH}/test/integration/nss_module.bats
fi
