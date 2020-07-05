# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- Project logo
- Run integration tests on CI
- Unix socket support

### Changed
- all queries resets a connection if the connection already exists (fixes aborted connections messages in groups queries)

## [0.9] - 2020-01-15
### Added
- First beta release, already deployed in a small scale operation.
