# Architecture

## Components

-> logger
-> mariadb adapter
-> NSS exports



NSS_STATUS_TRYAGAIN

    numeric value -2
NSS_STATUS_UNAVAIL

    numeric value -1
NSS_STATUS_NOTFOUND

    numeric value 0
NSS_STATUS_SUCCESS

    numeric value 1 


- passwd structure in getpwent is not NULL nor empty strings for items. It contains a previous searched entry, in my experiment it was
  _nss_maria_getpwent_r name:sshd password:x gecos: dir:/var/run/sshd shell:/usr/sbin/nologin buffer:sshd buflen:1024

this means the memory is not deallocated, nor emptied/nulled

