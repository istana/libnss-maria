#!/bin/bash
HOME_PATH="/home/libnss-maria"

if [[ -z $PRODUCTION ]]; then
  rm -rf "$HOME_PATH/Debug"
  mkdir "$HOME_PATH/Debug"

  cd /home/libnss-maria/Debug && cmake -D CMAKE_BUILD_TYPE=Debug .. && make && ctest --verbose
else
  rm -rf "$HOME_PATH/Release"
  mkdir "$HOME_PATH/Release"

  cd /home/libnss-maria/Release && cmake -D CMAKE_BUILD_TYPE=Release .. && make && ctest --verbose
fi

if [[ $? -eq 0 && -z $COMPILE_ONLY ]]; then
  sudo rm /lib/libnss_maria.so*
  sudo cp /home/libnss-maria/Debug/src/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2.0.0 &&
  sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so &&
  sudo ln -s /lib/libnss_maria.so.2.0.0 /lib/libnss_maria.so.2 &&
  sudo chmod 644 /lib/libnss_maria.so.2.0.0 &&

  sudo cp /home/libnss-maria/examples/sos-sso/nsswitch.conf /etc &&
  sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria.conf /etc &&
  sudo cp /home/libnss-maria/examples/sos-sso/libnss-maria-root.conf /etc

  ${HOME_PATH}/test/integration/nss_module.bats
fi
