/* kernelinfo.c - Linux kernel information viewer and system parameter modifier */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF 4096
#define MENU_EXIT 4

/* System parameter indices */
enum { EJECT, FILE_MAX, SHARED_MAX };

/* Information parameter indices */
enum { CDINFO, OS, RELEASE, VERSION };

/* System parameters that can be modified via /proc filesystem */
static const char *sys[] = {
    "/proc/sys/dev/cdrom/autoeject",  /* Eject CD on umount */
    "/proc/sys/fs/file-max",          /* Maximum open files per process */
    "/proc/sys/kernel/shmmax"         /* Maximum shared memory size */
};

/* Read-only system information paths */
static const char *info[] = {
    "/proc/sys/dev/cdrom/info",       /* CD-ROM information */
    "/proc/sys/kernel/ostype",        /* Operating system type */
    "/proc/sys/kernel/osrelease",     /* Kernel version */
    "/proc/sys/kernel/version"        /* Kernel build date */
};

/**
 * Read information from a /proc file
 * 
 * @param inf Path to the /proc file to read
 * @return Pointer to static buffer containing file contents, or NULL on error
 * @note Uses static buffer - not thread-safe, return value valid until next call
 */
char *get_info(const char *inf) {
    FILE *fp;
    static char buffer[BUF];
    size_t bytes_read;

    fp = fopen(inf, "r");
    if (fp == NULL) {
        perror("fopen()");
        return NULL;
    }

    bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    if (bytes_read == 0) {
        return NULL;
    }

    buffer[bytes_read] = '\0';
    return buffer;
}


/**
 * Write a value to a system parameter file in /proc
 * 
 * @param sys Path to the /proc file to write
 * @param set Value to write to the file
 */
void set_sys(const char *sys, unsigned long set) {
    FILE *fp;
    char buf[32];

    fp = fopen(sys, "w");
    if (fp == NULL) {
        perror("fopen()");
        printf("Press ENTER to continue\n");
        getchar();
        return;
    }

    snprintf(buf, sizeof(buf), "%lu", set);
    fprintf(fp, "%s", buf);
    fclose(fp);
}

/**
 * Display menu and handle user interaction for viewing/modifying system parameters
 */
int main(int argc, char **argv) {
    int choice;
    unsigned int file_max;
    unsigned long shared_max;

    do {
        /* Display current system information */
        printf("\n=== Current System Status ===\n");
        printf("Operating System: %s", get_info(info[OS]));
        printf("Kernel Version  : %s", get_info(info[RELEASE]));
        printf("Build Date      : %s", get_info(info[VERSION]));
        
        /* Display modifiable parameters */
        printf("====================================\n");
        printf("Modifiable Parameters:\n");
        printf("-0- Eject CD on umount        Current: %s", get_info(sys[EJECT]));
        printf("-1- Max open files per process Current: %s", get_info(sys[FILE_MAX]));
        printf("-2- Max shared memory (KB)     Current: %s", get_info(sys[SHARED_MAX]));
        
        /* Display information options */
        printf("====================================\n");
        printf("Information:\n");
        printf("-3- CD-ROM details\n");
        printf("====================================\n");
        printf("-4- EXIT\n");
        printf("Your choice (0-4): ");

        /* Read user input */
        do { 
            scanf("%d", &choice); 
        } while (getchar() != '\n');

        switch (choice) {
            case EJECT:
                /* Toggle CD autoeject on/off */
                if (strncmp("0", get_info(sys[EJECT]), 1) == 0) {
                    set_sys(sys[EJECT], 1);  /* Enable */
                } else {
                    set_sys(sys[EJECT], 0);  /* Disable */
                }
                break;

            case FILE_MAX:
                printf("Enter new value: ");
                do { 
                    scanf("%u", &file_max); 
                } while (getchar() != '\n');
                set_sys(sys[FILE_MAX], file_max);
                break;

            case SHARED_MAX:
                printf("Enter new value: ");
                do { 
                    scanf("%lu", &shared_max); 
                } while (getchar() != '\n');
                set_sys(sys[SHARED_MAX], shared_max);
                break;

            case 3:
                printf("\n%s", get_info(info[CDINFO]));
                printf("\nPress ENTER to continue\n");
                getchar();
                break;

            case MENU_EXIT:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid input\n");
        }
    } while (choice != MENU_EXIT);

    return EXIT_SUCCESS;
}
