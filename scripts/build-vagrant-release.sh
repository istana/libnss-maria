#!/bin/sh
vagrant ssh -c "RELEASE="1" COMPILE_ONLY="${COMPILE_ONLY}" TEST_USE_SUDO="1" /home/libnss-maria/scripts/compile_and_test.sh"
