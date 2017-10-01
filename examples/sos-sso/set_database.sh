#!/bin/bash

#dbsettings=$(cat db_credentials.txt)
dbsettings=$(cat)

dbname=$(echo $dbsettings | cut -f1 -d' ')
dbuser=$(echo $dbsettings | cut -f2 -d' ')
dbpass=$(echo $dbsettings | cut -f3 -d' ')

dbuser_root=$(echo $dbsettings | cut -f5 -d' ')
dbpass_root=$(echo $dbsettings | cut -f6 -d' ')

echo "db settings!"
echo $dbsettings

# sql injection ftw
read -r -d '' sql_commands <<- EOM
CREATE USER '$dbuser' IDENTIFIED BY '$dbpass';
CREATE USER '$dbuser_root' IDENTIFIED BY '$dbpass_root';
CREATE DATABASE '$dbname';

GRANT SELECT (`username`, `id`, `gid`, `gecos`, `homedir`, `shell`)
  ON `$dbname`.`users` TO '$dbuser';

GRANT SELECT (`username`, `password`, `lstchg`, `min`, `max`, `warn`, `inact`, `expire`, `flag`)
  ON `$dbname`.`users` TO '$dbuser_root';
EOM

echo "running mysql commands"
echo $sql_commands
echo $sql_commands | mysql
