# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Unreleased

## [1.0] - 2021-11-21
### Added
- mysql 8 compatibility

### Fixed
- segfault when cannot connect to the database - related to unix_socket value
- segfault when a config file is unreadable - happened everywhere listing and also find by name
- do not use uninitialized value - unix_socket config field

### Changed
- logger buffer value increased from 4k to 10k bytes
- do not log when root config is not readable
- add newlines to some log lines

### Removed
- remove config_db_settings binary

## [0.94] - 2021-09-18
### Fixed
- Memory leak in config load [thx bassbot123]

### Changed
- Move continuous integration from Travis CI to Github Actions
- Add -fanalyzer to compile options
- Update Debian Buster (10) to Bullseye (11)

## [0.93] - 2021-02-03
### Fixed
- Close config file properly after parsing
- String replace function is more thread safe
- `export VERBOSE=1` is passed via `./script/build-docker.sh` into build script
- test script explicitly sets UTF-8 for mysql command fixes UTF-8 failures in integration tests in Fedora

### Changed
- added support for `make install` command instead of copying and linking files manually
- update Dockerfile for *CentOS Stream*

### Added
- authselect configuration (thx @ondrejj)

## [0.92] - 2020-10-04
### Fixed
- Set mariadb/mysql client character encoding to UTF-8 - strings in a result are valid UTF-8 strings now
- Fixes "cannot connect to unix socket ''" when unix_socket nor host are defined in configuration file. Connects to "localhost" by default
- Set `export VERBOSE=1` before compilation to see detailed logs from the library

## [0.91] - 2020-07-09
### Added
- Project logo
- Run integration tests on CI
- Unix socket support
- Add the support for mysql/mariadb client options (mostly for TLS/SSL support)

### Changed
- [BREAKING CHANGE] Privilege separation for password and groups queries and shadow. This is to avoid password hashes to leak to regular users. New file `libnss-maria-root.conf`, see `examples` directory and `scripts/compile_and_test.sh`.

### Fixed
- All queries reset the connection if a connection already exists (fixes aborted connections messages in groups queries)

## [0.9] - 2020-01-15
### Added
- First beta release, already deployed in a small scale operation.
