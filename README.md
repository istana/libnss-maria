# libnss-maria

[![Build Status](https://travis-ci.org/istana/libnss-maria.svg?branch=master)](https://travis-ci.org/istana/libnss-maria)

Replacement for old libnss-mysql as naming service library in Linux.

You can store user information in MariaDB/MySQL database. E.g. `ls` then automatically shows user name from the database.


## Build && Test

Required libraries for building the library and test:

```
apt-get install cmake libssl-dev libc6-dev zlib1g-dev libconfig-dev libmysqlclient-dev
```

### Build

```
mkdir Debug
cd Debug
cmake -D CMAKE_BUILD_TYPE=Debug ..
make VERBOSE=1
```

### Release build (optimizations, warnings treated as errors)

```
mkdir Release
cd Release
cmake -D CMAKE_BUILD_TYPE=Release ..
make VERBOSE=1
```

### Run tests

`make test`

but to see the output from unit testing library (to see what failed):

`ctest --verbose`

## Architecture


```
naming service switch handler
**********************************
SQL Queries Dispatcher
**********************************
Configuration file parser
**********************************
Logger
```

items on lower layer are used by items on a higher layer, items on same layer are independent from each other

## Philosophy and Design

https://mariadb.com/kb/en/mariadb/mariadb-connector-c/

The MariaDB Connector/C is used to connect applications developed in C/C++ to MariaDB and MySQL databases. MySQL Connector/C is LGPL licensed.

Prior to version 2.1 the name for the library was MariaDB Client library for C.

### Why weird configuration format?

I've chosen libconfig, because:

- JSON hasn't multiline strings
- cannot found well maintained INI parser for linux, not sure about multiline strings
- libyaml is event based and I don't really understand it. Also YAML depends on indentation (or braces).
- libconfig is used by nginx, so it is not a big unknown. It has multiline strings and is multiplatform (BSD, ...)


## TODO

- the support for unix socket

### Parts

- cmake build setup - DONE
- configuration - DONE
- prepared statements (it's so hard) - WIP
- more examples - NOT STARTED
- log errors to systlog - NOT STARTED
- optimize via macros - NOT STARTED
- remove printf() and debugs && try it with valgrind - NOT STARTED

## Author + License

Written by Ivan Stana, 2015-2018. Released under these licenses: GNU GPL v3, LGPL v3 and MIT. I appreciate new testers, developers and users.


## Debug

https://github.com/Snaipe/Criterion/issues/206

Save this as criterion.gdb and start gdb with gdb ./yourtest -x criterion.gdb.

Then, from the gdb prompt, just call run, list children with info inferiors, switch inferiors with inferior <n>, and debug just as usual.
