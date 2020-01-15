# libnss-maria

[![Build Status](https://travis-ci.org/istana/libnss-maria.svg?branch=master)](https://travis-ci.org/istana/libnss-maria)

Replacement for old libnss-mysql as naming service library in Linux.

You can store user information in MariaDB/MySQL database. E.g. `ls` then automatically shows user name from the database, `getent` shows users and groups.

## Features

- cmake build system
- libconfig for configuration
- uses direct queries and real_escape_string
- uses threads.c from C11
- requirements: Glibc 2.28, GCC8, equivalent of Debian 10 (Buster) and newer, MySQL5.5+/MariaDB10.0+, mariadb-connector-c/mysql-client
    might work or compile on older systems, but it's untested

## TODO

- travis: set up Debian/Ubuntu/RHEL+MySQL/MariaDB+FreeBSD
- fix bug with too many users in a group
- permissions separation for pwd/grp and spw
- logo
- v1 version
- announce
- deb + rpm packages + universal package managers too
- the support for unix socket
- code quality analyzer in addition to strict compiler checks
- more unit tests

## Build && Test in Vagrant

```bash
brew cask install vagrant
brew cask install virtualbox
vagrant plugin install vagrant-vbguest

vagrant up
./scripts/build-vagrant.sh
# or ./scripts/build-vagrant-production.sh
```

The result is in `./Debug/src` or `./Release/src`directory.

## Build && Test in Docker

`docker-compose up`
`./scripts/build-docker.sh`

The result is in `./Debug/src` directory.

## Build && Test on a Linux system

Required libraries for building the library and test:

```
apt-get install coreutils build-essential cmake libmariadb-dev libconfig-dev syslog-ng-dev bats
apt-get install syslog-ng mariadb-client libconfig9 mariadb-server ruby pkg-config

./script/build-debug.sh
```

Set `PRODUCTION` variable to any value to build production build.

## License

Copyright (C) 2015-2020  Ivan Stana

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

### Other Software Included

- https://github.com/Snaipe/Criterion used as unit test framework (MIT)
- https://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c - for string replace function (CC4 BY)

## Related Software

- https://github.com/gmjosack/nss_debug
- https://github.com/Cellebyte/libnss-mysql-bg-1.5
- https://github.com/jandd/libnss-pgsql

Thanks for the inspiration and help.

## Debug

https://github.com/Snaipe/Criterion/issues/206

Save this as criterion.gdb and start gdb with gdb ./yourtest -x criterion.gdb.

Then, from the gdb prompt, just call run, list children with info inferiors, switch inferiors with inferior <n>, and debug just as usual.
