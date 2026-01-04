/**
 * kernelinfo.c - Linux kernel information viewer and system parameter modifier
 * 
 * This program demonstrates interaction with the Linux /proc filesystem to:
 * - View kernel version and system information
 * - Modify runtime kernel parameters (requires root/sudo)
 * - Toggle CD-ROM autoeject behavior
 * - Adjust system resource limits
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096
#define MENU_EXIT 4

/* Menu options for modifiable system parameters */
enum { EJECT, FILE_MAX, SHARED_MAX };

/* Menu options for read-only information */
enum { CDINFO, OS, RELEASE, VERSION };

/**
 * Writable system parameters accessible via /proc filesystem
 * These require root privileges to modify
 */
static const char *sys[] = {
    "/proc/sys/dev/cdrom/autoeject",  /* Auto-eject CD on unmount (0=off, 1=on) */
    "/proc/sys/fs/file-max",          /* Max open files system-wide */
    "/proc/sys/kernel/shmmax"         /* Max shared memory segment size (bytes) */
};

/**
 * Read-only system information paths in /proc filesystem
 */
static const char *info[] = {
    "/proc/sys/dev/cdrom/info",       /* CD-ROM drive capabilities */
    "/proc/sys/kernel/ostype",        /* OS type (e.g., "Linux") */
    "/proc/sys/kernel/osrelease",     /* Kernel version string */
    "/proc/sys/kernel/version"        /* Kernel build information */
};

/**
 * Read contents of a /proc filesystem file
 * 
 * @param path Filesystem path to read (typically under /proc)
 * @return Pointer to static buffer containing file contents, or NULL on error
 * 
 * @note Uses static buffer - not thread-safe
 * @note Return value is valid only until next call to this function
 * @note Caller should not free returned pointer
 */
static char *get_info(const char *path) {
    static char buffer[BUF_SIZE];
    FILE *fp;
    size_t bytes_read;

    /* Open proc file for reading */
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }

    /* Read entire file into buffer */
    bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    /* Handle empty files */
    if (bytes_read == 0) {
        return NULL;
    }

    /* Null-terminate the buffer */
    buffer[bytes_read] = '\0';
    return buffer;
}


/**
 * Write a numeric value to a system parameter file in /proc
 * 
 * @param path Path to the /proc file (must be writable, typically requires root)
 * @param value Numeric value to write
 * 
 * @note Requires appropriate permissions (usually root/sudo)
 * @note Displays error message and waits for user input on failure
 */
static void set_sys(const char *path, unsigned long value) {
    FILE *fp;

    /* Open proc file for writing */
    fp = fopen(path, "w");
    if (fp == NULL) {
        perror("fopen");
        printf("Note: Modifying system parameters requires root privileges.\n");
        printf("Press ENTER to continue\n");
        getchar();
        return;
    }

    /* Write value directly to file */
    fprintf(fp, "%lu", value);
    fclose(fp);
}

/**
 * Main program loop - display menu and handle user interactions
 * 
 * Provides an interactive interface to:
 * - View current kernel information
 * - Modify system parameters (requires root)
 * - Display CD-ROM information
 * 
 * @return EXIT_SUCCESS on normal termination
 */
int main(void) {
    int choice;
    unsigned long value;
    const char *current_value;

    do {
        /* Clear screen and display header */
        printf("\n");
        printf("╔════════════════════════════════════════╗\n");
        printf("║   Linux Kernel Information & Control  ║\n");
        printf("╚════════════════════════════════════════╝\n\n");

        /* Display current system information */
        printf("=== System Information ===\n");
        printf("OS Type        : %s", get_info(info[OS]));
        printf("Kernel Version : %s", get_info(info[RELEASE]));
        printf("Build Info     : %s", get_info(info[VERSION]));
        printf("\n");

        /* Display modifiable parameters with current values */
        printf("=== Modifiable Parameters (requires root) ===\n");
        printf("[0] CD autoeject on unmount  : %s", get_info(sys[EJECT]));
        printf("[1] Max open files (system)  : %s", get_info(sys[FILE_MAX]));
        printf("[2] Max shared memory (bytes): %s", get_info(sys[SHARED_MAX]));
        printf("\n");

        /* Display read-only information options */
        printf("=== Information ===\n");
        printf("[3] Display CD-ROM details\n");
        printf("\n");
        printf("[%d] Exit program\n", MENU_EXIT);
        printf("\nYour choice: ");

        /* Read and validate user input */
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            continue;
        }
        /* Consume remaining newline */
        while (getchar() != '\n');

        switch (choice) {
            case EJECT:
                /* Toggle CD autoeject (0=off, 1=on) */
                current_value = get_info(sys[EJECT]);
                if (current_value && current_value[0] == '0') {
                    printf("Enabling CD autoeject...\n");
                    set_sys(sys[EJECT], 1);
                } else {
                    printf("Disabling CD autoeject...\n");
                    set_sys(sys[EJECT], 0);
                }
                break;

            case FILE_MAX:
                /* Set maximum number of open files system-wide */
                printf("Enter new max open files: ");
                if (scanf("%lu", &value) == 1) {
                    set_sys(sys[FILE_MAX], value);
                    printf("Value updated (if you have permission).\n");
                } else {
                    printf("Invalid input.\n");
                }
                while (getchar() != '\n');
                break;

            case SHARED_MAX:
                /* Set maximum shared memory segment size */
                printf("Enter new max shared memory (bytes): ");
                if (scanf("%lu", &value) == 1) {
                    set_sys(sys[SHARED_MAX], value);
                    printf("Value updated (if you have permission).\n");
                } else {
                    printf("Invalid input.\n");
                }
                while (getchar() != '\n');
                break;

            case 3:
                /* Display detailed CD-ROM information */
                printf("\n=== CD-ROM Information ===\n");
                printf("%s", get_info(info[CDINFO]));
                printf("\nPress ENTER to continue...\n");
                getchar();
                break;

            case MENU_EXIT:
                printf("\nExiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter 0-%d.\n", MENU_EXIT);
        }
    } while (choice != MENU_EXIT);

    return EXIT_SUCCESS;
}
