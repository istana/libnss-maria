GRANT SELECT (`active`, `username`, `id`, `gid`, `gecos`, `homedir`, `shell`)
  ON `sos-sso-production`.`users` TO 'nss-maria-user'@'localhost';
GRANT SELECT (`active`, `username`, `id`, `gid`, `gecos`, `homedir`, `shell`)
  ON `sos-sso-production`.`users` TO 'nss-maria-user'@'172.%';

GRANT SELECT (`id`, `name`, `password`) ON `sos-sso-production`.`groups` TO 'nss-maria-user'@'localhost';
GRANT SELECT (`id`, `name`, `password`) ON `sos-sso-production`.`groups` TO 'nss-maria-user'@'172.%';

GRANT SELECT (`group_id`, `user_id`) ON `sos-sso-production`.`groups_users` TO 'nss-maria-user'@'localhost';
GRANT SELECT (`group_id`, `user_id`) ON `sos-sso-production`.`groups_users` TO 'nss-maria-user'@'172.%';

GRANT SELECT (`username`,`password`,`lstchg`,`min`,`max`,`warn`,`inact`,`expire`,`flag`)
  ON `sos-sso-production`.`users` TO 'nss-maria-root'@'localhost';
GRANT SELECT (`username`,`password`,`lstchg`,`min`,`max`,`warn`,`inact`,`expire`,`flag`)
  ON `sos-sso-production`.`users` TO 'nss-maria-root'@'172.%';

FLUSH PRIVILEGES;
