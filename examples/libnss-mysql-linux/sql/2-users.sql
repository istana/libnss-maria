DROP USER IF EXISTS 'nss-user'@'localhost';
DROP USER IF EXISTS 'nss-user'@'172.%';
DROP USER IF EXISTS 'nss-root'@'localhost';
DROP USER IF EXISTS 'nss-root'@'172.%';

GRANT USAGE ON *.* TO `nss-user`@`localhost` IDENTIFIED BY 'userpass';
GRANT USAGE ON *.* TO `nss-root`@`localhost` IDENTIFIED BY 'rootpass';
GRANT USAGE ON *.* TO `nss-user`@`172.%` IDENTIFIED BY 'userpass';
GRANT USAGE ON *.* TO `nss-root`@`172.%` IDENTIFIED BY 'rootpass';
