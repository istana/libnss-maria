# this creates also a user
DROP USER IF EXISTS 'nss-maria-user'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-user`@`localhost` IDENTIFIED BY 'Isabelle';
DROP USER  IF EXISTS 'nss-maria-root'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-root`@`localhost` IDENTIFIED BY 'Catherine';

DROP DATABASE IF EXISTS `sos-sso-production`;
CREATE DATABASE `sos-sso-production` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
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
