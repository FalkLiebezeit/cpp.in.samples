/* ResetTime.c - Reset file access and modification times to epoch (January 1, 1970) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>

/**
 * Reset a file's access and modification timestamps to the Unix epoch
 * 
 * This program demonstrates the use of the utime() system call to modify
 * file timestamps. It sets both access time (atime) and modification time
 * (mtime) to 0 (January 1, 1970, 00:00:00 UTC).
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv) {
    struct utimbuf times;

    /* Check for correct number of arguments */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Resets file access and modification times to epoch\n");
        return EXIT_FAILURE;
    }

    /* Set both timestamps to epoch (0 = January 1, 1970, 00:00:00 UTC) */
    times.actime = 0;   /* Access time */
    times.modtime = 0;  /* Modification time */

    /* Update the file's timestamps */
    if (utime(argv[1], &times) < 0) {
        perror("utime");
        return EXIT_FAILURE;
    }

    printf("Successfully reset timestamps for: %s\n", argv[1]);
    return EXIT_SUCCESS;
}
