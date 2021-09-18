/*
the configuration file uses libconfig library (syntax), i.e. is nginx-like
*/

#ifndef MARIA_CONFIG_STRUCT_H
#define MARIA_CONFIG_STRUCT_H

typedef struct Maria_configs {
  char dbhost[1024];
  char dbname[1024];
  char dbuser[1024];
  char dbpass[1024];
  long long dbport;
  char unix_socket[1024];
  char mariadb_client_config[1024];
  char dbrootuser[1024];
  char dbrootpass[1024];

  // "password" SQL queries
  // get user by name
  char getpwnam[8192];
  // get user by id
  char getpwuid[8192];
  // get all users
  char getpwent[8192];

  // shadow SQL queries
  // get shadow item by name
  char getspnam[8192];
  // get all shadow items
  char getspent[8192];

  // group SQL queries
  // get group by name
  char getgrnam[8192];
  // get group by id
  char getgrgid[8192];
  // get groups
  char getgrent[8192];

  // not in glibc - get users by group id
  char memsbygid[8192];

  // not in glibc - get groups by user name
  char gidsbymem[8192];

} Maria_config;

#endif
