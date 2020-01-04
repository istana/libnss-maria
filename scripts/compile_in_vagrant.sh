#!/bin/bash
HOME_PATH="/home/libnss-maria"

if [[ -z $PRODUCTION ]]; then
  TARGET="Debug"
else
  TARGET="Release"
fi

rm -rf "$HOME_PATH/$TARGET"
mkdir "$HOME_PATH/$TARGET"

cd /home/libnss-maria/${TARGET} && cmake -D CMAKE_BUILD_TYPE=${TARGET} .. && make && ctest --verbose

if [[ $? -eq 0 && -z $COMPILE_ONLY ]]; then
  sudo rm /lib/libnss_maria.so*
  sudo cp /home/libnss-maria/${TARGET}/src/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2.0.0 &&
  sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so &&
  sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2 &&
  sudo chmod 644 /lib/libnss_maria.so.2.0.0 &&

  sudo cp /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc &&
  sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria.conf /etc &&
  sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc

  ${HOME_PATH}/test/integration/nss_module.bats
fi
