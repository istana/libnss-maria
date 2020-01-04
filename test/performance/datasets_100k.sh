#!/bin/sh
cat /home/libnss-maria/examples/sos-sso/sql/1-db-and-users.sql | \
sudo mysql -u root &&
cat /home/libnss-maria/examples/sos-sso/sql/2-data-structures.sql | \
sudo mysql -u root sos-sso-production &&
cat /home/libnss-maria/examples/sos-sso/sql/3-privileges.sql | \
sudo mysql -u root sos-sso-production &&
cat /home/libnss-maria/examples/sos-sso/sql/4-data.sql | \
sudo mysql -u root sos-sso-production
/home/libnss-maria/test/performance/gen_datasets.rb 100000

/home/libnss-maria/test/performance/check_correctness.bats
