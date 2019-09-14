# this creates also a user
DROP USER IF EXISTS 'nss-maria-user'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-user`@`localhost` IDENTIFIED BY 'Isabelle';
DROP USER  IF EXISTS 'nss-maria-root'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-root`@`localhost` IDENTIFIED BY 'Catherine';

DROP DATABASE IF EXISTS `sos-sso-production`;
CREATE DATABASE `sos-sso-production` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
