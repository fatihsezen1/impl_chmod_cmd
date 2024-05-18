#include "csd_grp.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void exit_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

struct passwd *csd_getpwnam(const char *name)
{
    FILE *passwd_file;
    struct passwd *pwd_entry;
    char line[1024];

    if ((passwd_file = fopen("/etc/passwd", "r")) == NULL) {
        exit_sys("fopen");
    }

    while (fgets(line, sizeof(line), passwd_file)) {
        char *username = strtok(line, ":");
        if (strcmp(username, name) == 0) {
            pwd_entry = (struct passwd *)malloc(sizeof(struct passwd));
            if (pwd_entry == NULL) {
                fclose(passwd_file);
                exit_sys("malloc");
            }

            pwd_entry->pw_name = strdup(username);
            pwd_entry->pw_passwd = strdup(strtok(NULL, ":"));
            pwd_entry->pw_uid = atoi(strtok(NULL, ":"));
            pwd_entry->pw_gid = atoi(strtok(NULL, ":"));
            pwd_entry->pw_gecos = strdup(strtok(NULL, ":"));
            pwd_entry->pw_dir = strdup(strtok(NULL, ":"));
            pwd_entry->pw_shell = strdup(strtok(NULL, ":"));

            fclose(passwd_file);
            return pwd_entry;
        }
    }
}

struct passwd *csd_getpwuid(uid_t uid)
{
    FILE *passwd_file;
    struct passwd *pwd_entry;
    char line[1024];

    if ((passwd_file = fopen("/etc/passwd", "r")) == NULL) {
        exit_sys("fopen");
    }
    
    const char *useridstr;
    uid_t userid;
    while (fgets(line, sizeof(line), passwd_file)) {
        char *username = strtok(line, ":");

        useridstr = strtok(line, ":");
        userid = atoi(useridstr);

        if (userid == uid) {
            pwd_entry = (struct passwd *)malloc(sizeof(struct passwd));
            if (pwd_entry == NULL) {
                fclose(passwd_file);
                exit_sys("malloc");
            }

            pwd_entry->pw_name = strdup(username);
            pwd_entry->pw_passwd = strdup(strtok(NULL, ":"));
            pwd_entry->pw_uid = atoi(strtok(NULL, ":"));
            pwd_entry->pw_gid = atoi(strtok(NULL, ":"));
            pwd_entry->pw_gecos = strdup(strtok(NULL, ":"));
            pwd_entry->pw_dir = strdup(strtok(NULL, ":"));
            pwd_entry->pw_shell = strdup(strtok(NULL, ":"));

            fclose(passwd_file);
            return pwd_entry;
        }
    }
}

void csd_endpwent(void)
{
    FILE *passwd_file;
    if ((passwd_file = fopen("/etc/passwd", "r" )) == NULL) {
        exit_sys("fopen");
    }
    fclose(passwd_file);
}

struct passwd *csd_getpwent(void)
{
    FILE *passwd_file;
    struct passwd *pwd_entry;
    char line[1024];

    if ((passwd_file = fopen("/etc/passwd", "r")) == NULL) {
        exit_sys("fopen");
    }

    if (fgets(line, sizeof(line), passwd_file) != NULL) {
        char *username = strtok(line, ":");
        pwd_entry = (struct passwd*)malloc(sizeof(struct passwd));
        
        if (pwd_entry == NULL) { 
            fclose(passwd_file);
            exit_sys("malloc");
        }

        pwd_entry->pw_name = strdup(username);
        pwd_entry->pw_passwd = strdup(strtok(NULL, ":"));
        pwd_entry->pw_uid = atoi(strtok(NULL, ":"));
        pwd_entry->pw_gid = atoi(strtok(NULL, ":"));
        pwd_entry->pw_gecos = strdup(strtok(NULL, ":"));
        pwd_entry->pw_dir = strdup(strtok(NULL, ":"));
        pwd_entry->pw_shell = strdup(strtok(NULL, ":"));
    }

    return pwd_entry;
}

void csd_setpwent(void)
{
    FILE *passwd_file;
    if ((passwd_file = fopen("/etc/passwd", "r")) == NULL) {
        exit_sys("fopen");
    }

    fseek(passwd_file, 0, SEEK_SET);
}

struct group *csd_getgrnam(const char *name)
{
    FILE *grp_file;
    struct group *grp_entry;
    char line[1024];

    if ((grp_file = fopen("/etc/grp", "r")) == NULL) {
        exit_sys("fopen");
    }

    while (fgets(line, sizeof(line), grp_file)) {
        char *username = strtok(line, ":");
        if (strcmp(username, name) == 0) {
            grp_entry = (struct group *)malloc(sizeof(struct group));
            if (grp_entry == NULL) {
                fclose(grp_file);
                exit_sys("malloc");
            }

            grp_entry->gr_name = strdup(username);
            grp_entry->gr_passwd = strdup(strtok(NULL, ":"));
            grp_entry->gr_gid = atoi(strtok(NULL, ":"));
            grp_entry->gr_mem = atoi(strtok(NULL, ":"));

            fclose(grp_file);
            return grp_entry;
        }
    }
}

struct group *csd_getgrgid(gid_t gid)
{
    FILE *fp;
    struct group *grp;
    char line[1024];
    char *p;

    fp = fopen("/etc/group", "r");
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Split the line into fields separated by colons
        p = strtok(line, ":");
        if (p == NULL) continue; // Skip if empty line

        // Extract the group name
        char *groupname = p;

        // Move to the next field
        p = strtok(NULL, ":");
        if (p == NULL) continue;

        // Skip the password field
        p = strtok(NULL, ":");
        if (p == NULL) continue;

        // Extract the group ID
        gid_t groupid = atoi(p);

        // Check if this is the group we're looking for
        if (groupid == gid) {
            // Allocate memory for the group structure
            grp = (struct group *)malloc(sizeof(struct group));
            if (grp == NULL) {
                perror("malloc");
                fclose(fp);
                return NULL;
            }

            // Populate the group structure
            grp->gr_gid = groupid;
            grp->gr_name = groupname;

            // Extract and parse the member usernames
            p = strtok(NULL, ":");
            if (p != NULL) {
                // Count the number of members
                int member_count = 1;
                for (char *q = p; *q != '\0'; q++) {
                    if (*q == ',') member_count++;
                }

                // Allocate memory for the member array
                grp->gr_mem = (char **)malloc((member_count + 1) * sizeof(char *));
                if (grp->gr_mem == NULL) {
                    perror("malloc");
                    fclose(fp);
                    free(grp);
                    return NULL;
                }

                // Extract and populate the member array
                int i = 0;
                p = strtok(p, ",");
                while (p != NULL) {
                    grp->gr_mem[i++] = p;
                    p = strtok(NULL, ",");
                }
                grp->gr_mem[i] = NULL; // Null-terminate the member array
            } else {
                // No members found
                grp->gr_mem = NULL;
            }

            fclose(fp);
            return grp;
        }
    }

    // Group not found
    fclose(fp);
    return NULL;
    
}

void csd_endgrent(void)
{
    FILE *grp_file;
    if ((grp_file = fopen("/etc/group", "r")) == NULL) {
        exit_sys("fopen");
    }
    fclose(grp_file);
}

struct group *csd_getgrent(void)
{
    FILE *grp_file;
    struct group *grp_entry;
    char line[1024];

    if ((grp_file = fopen("/etc/group", "r")) == NULL) {
        exit_sys("fopen");
    }

    if (fgets(line, sizeof(line), grp_file) != NULL) {
        char *username = strtok(line, ":");
        grp_entry = (struct group*)malloc(sizeof(struct group));
        
        if (grp_entry == NULL) { 
            fclose(grp_file);
            exit_sys("malloc");
        }

        grp_entry->gr_name = strdup(username);
        grp_entry->gr_passwd = strdup(strtok(NULL, ":"));
        grp_entry->gr_gid = atoi(strtok(NULL, ":"));
        grp_entry->gr_mem = atoi(strtok(NULL, ":"));
    }

    return grp_entry;
}

void csd_setgrent(void)
{
    FILE *grp_file;
    if ((grp_file = fopen("/etc/grp", "r")) == NULL) {
        exit_sys("fopen");
    }

    fseek(grp_file, 0, SEEK_SET);
}