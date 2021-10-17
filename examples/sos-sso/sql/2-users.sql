DROP USER IF EXISTS 'nss-maria-user'@'localhost';
DROP USER IF EXISTS 'nss-maria-user'@'172.%';
DROP USER IF EXISTS 'nss-maria-root'@'localhost';
DROP USER IF EXISTS 'nss-maria-root'@'172.%';


CREATE USER 'nss-maria-user'@'localhost' IDENTIFIED BY 'Isabelle';
CREATE USER 'nss-maria-root'@'localhost' IDENTIFIED BY 'Catherine';
CREATE USER 'nss-maria-user'@'172.%' IDENTIFIED BY 'Isabelle';
CREATE USER 'nss-maria-root'@'172.%' IDENTIFIED BY 'Catherine';
GRANT USAGE ON *.* TO `nss-maria-user`@`localhost`;
GRANT USAGE ON *.* TO `nss-maria-root`@`localhost`;
GRANT USAGE ON *.* TO `nss-maria-user`@`172.%`;
GRANT USAGE ON *.* TO `nss-maria-root`@`172.%`;
