GRANT SELECT (`username`, `uid`, `gid`, `gecos`, `homedir`, `shell`, `password`, `lstchg`, `min`, `max`, `warn`, `inact`, `expire`, `flag`)
  ON `auth`.`users` TO 'nss-root'@'localhost';
GRANT SELECT (`username`, `uid`, `gid`, `gecos`, `homedir`, `shell`, `password`, `lstchg`, `min`, `max`, `warn`, `inact`, `expire`, `flag`)
  ON `auth`.`users` TO 'nss-root'@'172.%';

GRANT SELECT (`name`, `password`, `gid`) ON `auth`.`groups` TO 'nss-root'@'localhost';
GRANT SELECT (`name`, `password`, `gid`) ON `auth`.`groups` TO 'nss-root'@'172.%';

GRANT SELECT (`username`, `uid`, `gid`, `gecos`, `homedir`, `shell`) ON `auth`.`users` TO 'nss-user'@'localhost';
GRANT SELECT (`username`, `uid`, `gid`, `gecos`, `homedir`, `shell`) ON `auth`.`users` TO 'nss-user'@'172.%';

GRANT SELECT (`name`, `password`, `gid`) ON `auth`.`groups` TO 'nss-user'@'localhost';
GRANT SELECT (`name`, `password`, `gid`) ON `auth`.`groups` TO 'nss-user'@'172.%';

GRANT SELECT (`username`, `gid`) ON `auth`.`grouplist` TO 'nss-user'@'localhost';
GRANT SELECT (`username`, `gid`) ON `auth`.`grouplist` TO 'nss-user'@'172.%';

GRANT SELECT (`username`, `gid`) ON `auth`.`grouplist` TO 'nss-root'@'localhost';
GRANT SELECT (`username`, `gid`) ON `auth`.`grouplist` TO 'nss-root'@'172.%';
