/* my_getpid.c - Demonstrates retrieving process ID via /proc/self symlink */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Retrieves the current process ID by reading the /proc/self symlink
 * 
 * This program demonstrates an alternative way to get the process ID
 * by reading the /proc/self symbolic link, which always points to the
 * /proc directory of the calling process.
 * 
 * @return EXIT_SUCCESS on successful execution
 */
int main(void) {
    char buf[64];
    int pid;
    ssize_t len;

    /* Read the /proc/self symlink to get our process ID */
    len = readlink("/proc/self", buf, sizeof(buf) - 1);
    if (len == -1) {
        perror("readlink");
        return EXIT_FAILURE;
    }
    
    /* Null-terminate the buffer */
    buf[len] = '\0';
    
    /* Parse the process ID from the buffer */
    if (sscanf(buf, "%d", &pid) != 1) {
        fprintf(stderr, "Failed to parse process ID\n");
        return EXIT_FAILURE;
    }
    
    printf("My process ID is: %d\n", pid);
    printf("(Same as getpid(): %d)\n", getpid());
    
    return EXIT_SUCCESS;
}
