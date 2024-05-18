#include <sys/types.h>

struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};

struct group {
    char   *gr_name;        /* group name */
    char   *gr_passwd;      /* group password */
    gid_t   gr_gid;         /* group ID */
    char  **gr_mem;         /* NULL-terminated array of pointers
                               to names of group members */
};

struct passwd *csd_getpwnam(const char *name);
struct passwd *csd_getpwuid(uid_t uid);
void csd_endpwent(void);
struct passwd *csd_getpwent(void);
void csd_setpwent(void);

struct group *csd_getgrnam(const char *name);
struct group *csd_getgrgid(gid_t gid);
void csd_endgrent(void);
struct group *csd_getgrent(void);
void csd_setgrent(void);

void exit_sys(const char *msg);
