#!/bin/bash

function run_command {
  vagrant ssh -c "$1"
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

run_command "${existing_user}"

if [ "$?" -gt 0 ]; then
  echo "sanity check: $existing_user TEST FAIL"
else
  echo "sanity check: $existing_user TEST SUCCESS"
fi

echo -e "\n"

run_command "${maria_user}"

if [ "$?" -gt 0 ]; then
  echo "$maria_user TEST FAIL"
else
  echo "$maria_user TEST SUCCESS"
fi

echo -e "\n"

run_command "${maria_user_listing}"

if [ "$?" -gt 0 ]; then
  echo "$maria_user_listing TEST FAIL"
else
  echo "$maria_user_listing TEST SUCCESS"
fi

maria_user_id="getent passwd 8000"

echo -e "\n"

run_command "${maria_user_id}"

if [ "$?" -gt 0 ]; then
  echo "$maria_user_id TEST FAIL"
else
  echo "$maria_user_id TEST SUCCESS"
fi

exit 0;
