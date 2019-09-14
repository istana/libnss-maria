GRANT USAGE ON `sos-sso-production`.* TO 'nss-maria-user'@'localhost';
GRANT USAGE ON `sos-sso-production`.* TO 'nss-maria-root'@'localhost';

-- GRANT SELECT (col1), INSERT (col1,col2) ON mydb.mytbl TO 'someuser'@'somehost';

GRANT SELECT (`username`, `id`, `gid`, `gecos`, `homedir`, `shell`)
  ON `sos-sso-production`.`users` TO 'nss-maria-user'@'localhost';

GRANT SELECT (`id`, `name`, `password`)
  ON `sos-sso-production`.`groups` TO 'nss-maria-user'@'localhost';

-- root only
GRANT SELECT (`username`,`password`,`lstchg`,`min`,`max`,`warn`,`inact`,`expire`,`flag`)
  ON `sos-sso-production`.`users` TO 'nss-maria-root'@'localhost';


FLUSH PRIVILEGES;
