# this creates also a user
DROP USER IF EXISTS 'nss-maria-user'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-user`@`localhost` IDENTIFIED BY 'Isabelle';
DROP USER  IF EXISTS 'nss-maria-root'@'localhost';
GRANT USAGE ON *.* TO `nss-maria-root`@`localhost` IDENTIFIED BY 'Catherine';

DROP DATABASE IF EXISTS `sos-sso-production`;
CREATE DATABASE `sos-sso-production` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
GRANT USAGE ON `sos-sso-production`.* TO 'nss-maria-user'@'localhost';
GRANT USAGE ON `sos-sso-production`.* TO 'nss-maria-root'@'localhost';

FLUSH PRIVILEGES;

USE `sos-sso-production`;


/* ************************************************************** */
/* ************************************************************** */
/* ************************************************************** */

-- MySQL dump 10.15  Distrib 10.0.24-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: sos-sso-production
-- ------------------------------------------------------
-- Server version 10.0.24-MariaDB-1~jessie

--
-- Table structure for table `admins`
--

CREATE TABLE `admins` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `encrypted_password` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `remember_created_at` datetime DEFAULT NULL,
  `sign_in_count` int(11) NOT NULL DEFAULT '0',
  `current_sign_in_at` datetime DEFAULT NULL,
  `last_sign_in_at` datetime DEFAULT NULL,
  `current_sign_in_ip` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `last_sign_in_ip` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `created_at` datetime DEFAULT NULL,
  `updated_at` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `index_admins_on_email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `aliases`
--

CREATE TABLE `aliases` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `user_id` int(11) NOT NULL,
  `created_at` datetime DEFAULT NULL,
  `updated_at` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `index_aliases_on_active` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `cui`
--

CREATE TABLE `cui` (
  `clientipaddress` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `callingstationid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `cui` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `creationdate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `lastaccounting` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`username`,`clientipaddress`,`callingstationid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `groups`
--

CREATE TABLE `groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'x',
  `created_at` datetime DEFAULT NULL,
  `updated_at` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unqname` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=8041 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `groups_users`
--

CREATE TABLE `groups_users` (
  `group_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  KEY `index_groups_users_on_group_id_and_user_id` (`group_id`,`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `nas`
--

CREATE TABLE `nas` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nasname` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shortname` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `xtype` varchar(255) COLLATE utf8_unicode_ci DEFAULT 'other',
  `ports` int(11) DEFAULT NULL,
  `secret` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'secret',
  `server` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `community` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `description` varchar(255) COLLATE utf8_unicode_ci DEFAULT 'RADIUS Client',
  PRIMARY KEY (`id`),
  KEY `nasname` (`nasname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radacct`
--

CREATE TABLE `radacct` (
  `radacctid` bigint(20) NOT NULL,
  `acctsessionid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `acctuniqueid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `groupname` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `realm` varchar(255) COLLATE utf8_unicode_ci DEFAULT '',
  `nasipaddress` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `nasportid` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `nasporttype` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `acctstarttime` datetime DEFAULT NULL,
  `acctstoptime` datetime DEFAULT NULL,
  `acctsessiontime` bigint(20) DEFAULT NULL,
  `acctauthentic` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `connectinfo_start` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `connectinfo_stop` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `acctinputoctets` bigint(20) DEFAULT NULL,
  `acctoutputoctets` bigint(20) DEFAULT NULL,
  `calledstationid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `callingstationid` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `acctterminatecause` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `servicetype` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `framedprotocol` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `framedipaddress` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `acctstartdelay` bigint(20) DEFAULT NULL,
  `acctstopdelay` bigint(20) DEFAULT NULL,
  `xascendsessionsvrkey` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`radacctid`),
  UNIQUE KEY `acctuniqueid` (`acctuniqueid`),
  KEY `username` (`username`),
  KEY `framedipaddress` (`framedipaddress`),
  KEY `acctsessionid` (`acctsessionid`),
  KEY `acctsessiontime` (`acctsessiontime`),
  KEY `acctstarttime` (`acctstarttime`),
  KEY `acctstoptime` (`acctstoptime`),
  KEY `nasipaddress` (`nasipaddress`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radcheck`
--

CREATE TABLE `radcheck` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `attr` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `op` varchar(2) COLLATE utf8_unicode_ci NOT NULL DEFAULT '==',
  `value` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `username` (`username`(32))
) ENGINE=InnoDB AUTO_INCREMENT=1568 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radgroupcheck`
--

CREATE TABLE `radgroupcheck` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `groupname` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `attr` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `op` varchar(2) COLLATE utf8_unicode_ci NOT NULL DEFAULT '==',
  `value` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `groupname` (`groupname`(32))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radgroupreply`
--

CREATE TABLE `radgroupreply` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `groupname` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `attr` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `op` varchar(2) COLLATE utf8_unicode_ci NOT NULL DEFAULT '==',
  `value` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `groupname` (`groupname`(32))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radippool`
--

CREATE TABLE `radippool` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pool_name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `framedipaddress` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `nasipaddress` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `calledstationid` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `callingstationid` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `expiry_time` datetime DEFAULT NULL,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `pool_key` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  KEY `radippool_poolname_expire` (`pool_name`,`expiry_time`),
  KEY `framedipaddress` (`framedipaddress`),
  KEY `radippool_nasip_poolkey_ipaddress` (`nasipaddress`,`pool_key`,`framedipaddress`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radpostauth`
--

CREATE TABLE `radpostauth` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `pass` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `reply` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `authdate` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1068278 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radreply`
--

CREATE TABLE `radreply` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `attr` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `op` varchar(2) COLLATE utf8_unicode_ci NOT NULL DEFAULT '==',
  `value` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `username` (`username`(32))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `radusergroup`
--

CREATE TABLE `radusergroup` (
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `groupname` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `priority` int(11) NOT NULL DEFAULT '1',
  KEY `username` (`username`(32))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `schema_migrations`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schema_migrations` (
  `version` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  UNIQUE KEY `unique_schema_migrations` (`version`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `gid` bigint(20) NOT NULL,
  `gecos` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `homedir` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shell` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '/usr/bin/rssh',
  `password` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'x',
  `lstchg` bigint(20) NOT NULL DEFAULT '1',
  `min` bigint(20) NOT NULL DEFAULT '0',
  `max` bigint(20) NOT NULL DEFAULT '9999',
  `warn` bigint(20) NOT NULL DEFAULT '30',
  `inact` bigint(20) NOT NULL DEFAULT '0',
  `expire` bigint(20) NOT NULL DEFAULT '-1',
  `flag` tinyint(4) NOT NULL DEFAULT '0',
  `quota_mass` bigint(20) NOT NULL DEFAULT '52428800',
  `quota_inodes` bigint(20) NOT NULL DEFAULT '15000',
  `active` tinyint(1) NOT NULL DEFAULT '1',
  `created_at` datetime DEFAULT NULL,
  `updated_at` datetime DEFAULT NULL,
  `ntlm_password` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unqusername` (`username`),
  KEY `index_users_on_active` (`active`)
) ENGINE=InnoDB AUTO_INCREMENT=8828 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `version_associations`
--

CREATE TABLE `version_associations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `version_id` int(11) DEFAULT NULL,
  `foreign_key_name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `foreign_key_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `index_version_associations_on_version_id` (`version_id`),
  KEY `index_version_associations_on_foreign_key` (`foreign_key_name`,`foreign_key_id`)
) ENGINE=InnoDB AUTO_INCREMENT=192 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `versions`
--

CREATE TABLE `versions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `item_type` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `item_id` int(11) NOT NULL,
  `event` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `whodunnit` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `object` text COLLATE utf8_unicode_ci,
  `created_at` datetime DEFAULT NULL,
  `object_changes` text COLLATE utf8_unicode_ci,
  `transaction_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `index_versions_on_item_type_and_item_id` (`item_type`,`item_id`),
  KEY `index_versions_on_transaction_id` (`transaction_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9894 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Table structure for table `wimax`
--

CREATE TABLE `wimax` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `authdate` datetime NOT NULL,
  `spi` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `mipkey` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `lifetime` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `username` (`username`),
  KEY `spi` (`spi`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- Dump completed on 2016-03-04 23:33:57


-- GRANT SELECT (col1), INSERT (col1,col2) ON mydb.mytbl TO 'someuser'@'somehost';

GRANT SELECT (`username`, `id`, `gid`, `gecos`, `homedir`, `shell`)
  ON `sos-sso-production`.`users` TO 'nss-maria-user'@'localhost';

GRANT SELECT (`id`, `name`, `password`)
  ON `sos-sso-production`.`groups` TO 'nss-maria-user'@'localhost';

-- root only
GRANT SELECT (`username`,`password`,`lstchg`,`min`,`max`,`warn`,`inact`,`expire`,`flag`)
  ON `sos-sso-production`.`users` TO 'nss-maria-root'@'localhost';
