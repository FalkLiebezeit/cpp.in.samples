/* my_stat.c - Display file information and permissions for current directory */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>

/**
 * Lists all files in the current directory with their type and permissions
 * 
 * For each file/directory, displays:
 * - File type (regular file, directory, device, FIFO, etc.)
 * - File name
 * - Permission bits in rwx format
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv) {
    DIR *dir;
    struct dirent *dir_entry;
    
    /* Permission characters for display */
    const char *rwx = "rwxrwxrwx";
    
    /* Permission bit masks for user, group, and others */
    int bits[] = {
        S_IRUSR, S_IWUSR, S_IXUSR,  /* User permissions: read, write, execute */
        S_IRGRP, S_IWGRP, S_IXGRP,  /* Group permissions: read, write, execute */
        S_IROTH, S_IWOTH, S_IXOTH   /* Other permissions: read, write, execute */
    };

    /* Open the current directory */
    dir = opendir(".");
    if (dir == NULL) {
        fprintf(stderr, "Error opening directory: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    /* Read all entries in the directory */
    while ((dir_entry = readdir(dir)) != NULL) {
        struct stat file_stat;
        int i;
        char perm_str[10];

        /* Get file attributes */
        if (stat(dir_entry->d_name, &file_stat) == -1) {
            fprintf(stderr, "Error stat'ing %s: %s\n", 
                    dir_entry->d_name, strerror(errno));
            continue;  /* Continue with next file instead of exiting */
        }

        /* Determine and display file type */
        if (S_ISREG(file_stat.st_mode))
            printf("Regular file        : ");
        else if (S_ISDIR(file_stat.st_mode))
            printf("Directory           : ");
        else if (S_ISCHR(file_stat.st_mode))
            printf("Character device    : ");
        else if (S_ISBLK(file_stat.st_mode))
            printf("Block device        : ");
        else if (S_ISFIFO(file_stat.st_mode))
            printf("FIFO/Named pipe     : ");
        else if (S_ISLNK(file_stat.st_mode))
            printf("Symbolic link       : ");
        else if (S_ISSOCK(file_stat.st_mode))
            printf("Socket              : ");
        else
            printf("Unknown file type   : ");

        /* Build permission string */
        for (i = 0; i < 9; i++) {
            perm_str[i] = (file_stat.st_mode & bits[i]) ? rwx[i] : '-';
        }
        perm_str[9] = '\0';

        /* Display filename and permissions */
        printf("%-20s [%s]\n", dir_entry->d_name, perm_str);
    }

    closedir(dir);
    return EXIT_SUCCESS;
}
