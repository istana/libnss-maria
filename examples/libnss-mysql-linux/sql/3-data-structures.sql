CREATE TABLE `groups` (
  name varchar(16) NOT NULL default '',
  password varchar(34) NOT NULL default 'x',
  gid int(11) NOT NULL auto_increment,
  PRIMARY KEY  (gid)
) AUTO_INCREMENT=5000;

CREATE TABLE `grouplist` (
  rowid int(11) NOT NULL auto_increment,
  gid int(11) NOT NULL default '0',
  username char(16) NOT NULL default '',
  PRIMARY KEY  (rowid)
);

CREATE TABLE `users` (
  username varchar(16) NOT NULL default '',
  uid int(11) NOT NULL auto_increment,
  gid int(11) NOT NULL default '5000',
  gecos varchar(128) NOT NULL default '',
  homedir varchar(255) NOT NULL default '',
  shell varchar(64) NOT NULL default '/bin/bash',
  password varchar(128) NOT NULL default 'x',
  lstchg bigint(20) NOT NULL default '1',
  min bigint(20) NOT NULL default '0',
  max bigint(20) NOT NULL default '99999',
  warn bigint(20) NOT NULL default '0',
  inact bigint(20) NOT NULL default '0',
  expire bigint(20) NOT NULL default '-1',
  flag bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (uid),
  UNIQUE KEY username (username),
  KEY uid (uid)
) AUTO_INCREMENT=5000;
