# <img src="./libnss-maria-logo.svg" width="96" height="96"> libnss-maria

[![Build Status](https://travis-ci.org/istana/libnss-maria.svg?branch=master)](https://travis-ci.org/istana/libnss-maria)

Replacement for old libnss-mysql as naming service library in Linux.

You can store user information in MariaDB/MySQL database. E.g. `ls` then automatically shows user name from the database, `getent` shows users and groups.

## Features

- implements `password`, `shadow` and `group` getters
- `cmake` build system
- `libconfig` for configuration
- uses direct queries and `real_escape_string`
- uses `threads.c` from `C11`
- requirements: Glibc 2.28, GCC8, equivalent of Debian 10 (Buster) and newer, MySQL5.5+/MariaDB10.0+, mariadb-connector-c/mysql-client. Might work or compile on older systems, but it's untested
- tested systems - Archlinux, Centos, Debian (bullseye/stable), Fedora, latest Ubuntu, Ubuntu LTS
- both unix socket and host are supported
- shouldn't be used with SUID programs

## TODO

- v1 version
- announce
- deb + rpm packages
- architecture like nss_ldapd would be nice

## Build && Test in Vagrant

```bash
brew cask install vagrant
brew cask install virtualbox
vagrant plugin install vagrant-vbguest

vagrant up
./scripts/build-vagrant.sh
# or ./scripts/build-vagrant-release.sh
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

./scripts/build-debug.sh

or

mkdir Debug
cd Debug
cmake ..
make
(sudo) make install
```

Set `RELEASE` variable to any value to build a release build.

## Installation & Usage

See `examples` and `scripts/compile_and_test.sh` to see how to set it up and use.

## License

Copyright (C) 2015-2021  Ivan Stana

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

## Thanks

- @xHire for answering and not answering my infinite number of questions about C
- and other people answering my quesions

## Related Software

- https://github.com/gmjosack/nss_debug
- https://github.com/Cellebyte/libnss-mysql-bg-1.5
- https://github.com/jandd/libnss-pgsql

Thanks for the inspiration and help.

## Links

- https://freshcode.club/projects/libnss-maria

## Debug

https://github.com/Snaipe/Criterion/issues/206

Save this as criterion.gdb and start gdb with gdb ./yourtest -x criterion.gdb.

Then, from the gdb prompt, just call run, list children with info inferiors, switch inferiors with inferior <n>, and debug just as usual.
