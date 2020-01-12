#!/bin/sh
vagrant ssh -c "COMPILE_ONLY="${COMPILE_ONLY}" TEST_USE_SUDO="1" /home/libnss-maria/scripts/compile_and_test.sh"
