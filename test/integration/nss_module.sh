#!/bin/bash

function run_command {
  vagrant ssh -c "$1"
}

function run_test {
  run_command "$1"

  if [ "$?" -gt 0 ]; then
    echo "$1 TEST FAIL"
  else
    echo "$1 TEST SUCCESS"
  fi 
}

run_command "cat /home/libnss-maria/examples/sos-sso/sql/1-db-and-users.sql | \
sudo mysql -u root" &&
run_command "cat /home/libnss-maria/examples/sos-sso/sql/2-data-structures.sql | \
sudo mysql -u root sos-sso-production" &&
run_command "cat /home/libnss-maria/examples/sos-sso/sql/3-privileges.sql | \
sudo mysql -u root sos-sso-production" &&
run_command "cat /home/libnss-maria/examples/sos-sso/sql/4-data.sql | \
sudo mysql -u root sos-sso-production"

echo -e "\nSetup done...\n"

existing_user="getent passwd root"
maria_user="getent passwd katarina"
maria_user_listing="getent passwd | grep katarina"
maria_user_id="getent passwd 8000"
maria_user_shadow_name="getent shadow katarina"
maria_group="getent group clan"
maria_group_id="getent group 9000"

run_test "${existing_user}"
run_test "${maria_user}"
run_test "${maria_user_listing}"
run_test "${maria_user_id}"
run_test "${maria_user_shadow_name}"
run_test "${maria_group}"
run_test "${maria_group_id}"

exit 0;
