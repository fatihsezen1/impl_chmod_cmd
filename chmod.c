#include <stdio.h>
#include <stdlib.h>
#include "csd_grp.h"

void usage();

int main(/* int argc, char *argv[] */)
{
/*     if (argc != 3) {
        usage();
    }

    const char *permissions = argv[1];  //u+rw
    const char *file = argv[2];         //test.txt

    // Check if file exists
    if (access(file, F_OK) == -1) {
        printf("Error: File '%s' not found.\n", file);
        exit_sys("access");
    } */

    printf("asdasdads\n\n\n");
    struct passwd *pwd_entry;

    // /etc/passwd dosyasından kullanıcı bilgilerini al
    while ((pwd_entry = csd_getpwent()) != NULL) {
        printf("Username: %s\n", pwd_entry->pw_name);
        printf("Password: %s\n", pwd_entry->pw_passwd);
        printf("UID: %d\n", pwd_entry->pw_uid);
        printf("GID: %d\n", pwd_entry->pw_gid);
        printf("Gecos: %s\n", pwd_entry->pw_gecos);
        printf("Home directory: %s\n", pwd_entry->pw_dir);
        printf("Shell: %s\n", pwd_entry->pw_shell);
        printf("\n");
        
        // Belleği temizle
        free(pwd_entry->pw_name);
        free(pwd_entry->pw_passwd);
        free(pwd_entry->pw_gecos);
        free(pwd_entry->pw_dir);
        free(pwd_entry->pw_shell);
        free(pwd_entry);
    }

    return 0;
}

void usage()
{
    printf("Usage: ./chmod [OPTION]... MODE[,MODE]... FILE...\n");
    printf("Example: ./chmod u+rw test.txt\n");
    exit(EXIT_FAILURE);
}


