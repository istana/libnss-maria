#include <nss.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include "configuration.h"

// password, pwd.h
enum nss_status _nss_maria_getpwnam_r(const char *name, struct passwd *pwd,
		char *buffer, size_t buflen, int *errnop);

enum nss_status _nss_maria_getpwuid_r(uid_t uid, struct passwd *pwd,
		char *buffer, size_t buflen, int *errnop);

enum nss_status _nss_maria_getpwent_r(struct passwd *result, char *buffer, size_t buflen, int *errnop);

// groups, from grp.h
enum nss_status _nss_maria_getgrnam_r(const char *name, struct group *grp,
		char *buffer, size_t buflen, int *errnop);

enum nss_status _nss_maria_getgrid_r(gid_t gid, struct group *grp,
		char *buffer, size_t buflen, int *errnop);

enum nss_status _nss_maria_getgrent_r(struct group *result,
		char *buffer, size_t buflen, int *errnop);

// shadow record, from shadow.h
enum nss_status _nss_maria_getspent_r(struct spwd *pwd,
		char *buffer, size_t buflen, int *errnop);

enum nss_status _nss_maria_getspnam_r(const char *name, struct spwd *pwd,
		char *buffer, size_t buflen, int *errnop);
