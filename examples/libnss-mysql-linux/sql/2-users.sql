DROP USER IF EXISTS 'nss-user'@'localhost';
DROP USER IF EXISTS 'nss-user'@'172.%';
DROP USER IF EXISTS 'nss-root'@'localhost';
DROP USER IF EXISTS 'nss-root'@'172.%';

CREATE USER 'nss-user'@'localhost' IDENTIFIED BY 'userpass';
CREATE USER 'nss-root'@'localhost' IDENTIFIED BY 'rootpass';
CREATE USER 'nss-user'@'172.%' IDENTIFIED BY 'userpass';
CREATE USER 'nss-root'@'172.%' IDENTIFIED BY 'rootpass';
GRANT USAGE ON *.* TO `nss-user`@`localhost`;
GRANT USAGE ON *.* TO `nss-root`@`localhost`;
GRANT USAGE ON *.* TO `nss-user`@`172.%`;
GRANT USAGE ON *.* TO `nss-root`@`172.%`;
