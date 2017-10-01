#!/bin/sh

dbsettings=`./Debug/src/config_db_settings examples/sos-sso/libnss-maria.conf`
dbsettings_root=`./Debug/src/config_db_settings examples/sos-sso/libnss-maria-root.conf`

echo $dbsettings > './Debug/test/db_credentials.txt'
echo $dbsettings_root >> './Debug/test/db_credentials.txt'
