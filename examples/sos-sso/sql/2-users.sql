# this creates also a user
DROP USER IF EXISTS 'nss-maria-user'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-user`@`localhost` IDENTIFIED BY 'Isabelle';
DROP USER  IF EXISTS 'nss-maria-root'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-root`@`localhost` IDENTIFIED BY 'Catherine';
