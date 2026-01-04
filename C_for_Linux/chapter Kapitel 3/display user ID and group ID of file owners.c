/* ugid.c - Display user ID and group ID of file owners */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

/**
 * Display the user ID (UID) and group ID (GID) for one or more files
 * 
 * This program uses the stat() system call to retrieve file attributes
 * and displays the numeric UID and GID of the file owner.
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of filenames to query
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv) {
    struct stat file_stat;

    /* Check for required arguments */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file(s)>\n", argv[0]);
        fprintf(stderr, "Displays user ID and group ID for specified file(s)\n");
        return EXIT_FAILURE;
    }

    /* Process each file argument */
    argv++;  /* Skip program name */
    while (*argv != NULL) {
        /* Get file status */
        if (stat(*argv, &file_stat) < 0) {
            fprintf(stderr, "Error stat'ing '%s': %s\n", *argv, strerror(errno));
            argv++;
            continue;  /* Continue with next file instead of exiting */
        }

        /* Display file information */
        printf("%-18s\n", *argv);
        printf("  User ID  : %u\n", file_stat.st_uid);
        printf("  Group ID : %u\n\n", file_stat.st_gid);

        argv++;
    }

    return EXIT_SUCCESS;
}
