# libnss-maria

Replacement for old libnss-mysql as naming service library.


For test:

```
apt-get install libssl-dev libltdl-dev libc6-dev
```

build

```
mkdir Debug
cmake -D CMAKE_BUILD_TYPE=Debug ..
make VERBOSE=1
```


https://mariadb.com/kb/en/mariadb/mariadb-connector-c/

The MariaDB Connector/C is used to connect applications developed in C/C++ to MariaDB and MySQL databases. MySQL Connector/C is LGPL licensed.

Prior to version 2.1 the name for the library was MariaDB Client library for C.

## Why weird configuration format?

I've chosen libconfig, because:

- JSON hasn't multiline strings
- cannot found well maintained INI parser for linux, not sure about multiline strings
- libyaml is event based and I don't really understand it. Also YAML depends on indentation (or braces).
- libconfig is used by nginx, so it is not a big unknown. It has multiline strings and is multiplatform (BSD, ...)
