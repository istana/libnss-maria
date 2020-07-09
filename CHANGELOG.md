# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.91] - 2020-07-09
### Added
- Project logo
- Run integration tests on CI
- Unix socket support
- Add the support for mysql/mariadb client options (mostly for TLS/SSL support)

### Changed
- [BREAKING CHANGE] Privilege separation for password and groups queries and shadow. This is to avoid password hashes to leak to regular users. New file `libnss-maria-root.conf`, see `examples` directory and `scripts/compile_and_test.sh`.

### Fixed
- all queries resets a connection if the connection already exists (fixes aborted connections messages in groups queries)

## [0.9] - 2020-01-15
### Added
- First beta release, already deployed in a small scale operation.
