# adapted from https://github.com/saknopper/libnss-mysql/blob/master/sample/linux/sample_database_mysql8.sql

#
# $Id$
#
#                THIS DATABASE IS INTENDED FOR Linux
#
# Use 'mysql -u root -p < sample_database_mysql8.sql' to load this example into your
# MySQL server.
# This example will:
#   1) create a database called 'auth'
#   2) add three tables: 'users', 'groups' and 'grouplist'
#   3) add some data to each table
#   4) create two MySQL users ('nss-user' and 'nss-root') with appropriate
#      SELECT privs.
#
# With a properly-functioning libnss-mysql, you should be able to log into
# the system as 'cinergi' with a password of 'cinergi'.  'cinergi' should be
# a member of the group 'foobaz' as well.
#
# This is intended as an *example* and is perhaps not the best use of
# datatypes, space/size, data normalization, etc.
#
DROP DATABASE IF EXISTS `auth`;
CREATE DATABASE `auth`;
