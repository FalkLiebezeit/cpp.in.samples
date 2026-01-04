/* myinfo.c - Interactive Linux system information viewer via /proc filesystem */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF 4096  /* Buffer size for reading /proc files */

/* Menu options for system information categories */
enum { CPU, DEV, DMA, INT, IOP, MEM, VERS, SCSI, EXIT };

/* Paths to /proc filesystem files containing system information */
const char *info[] = {
    "/proc/cpuinfo",      /* CPU information */
    "/proc/devices",      /* Character and block devices */
    "/proc/dma",          /* DMA channels in use */
    "/proc/interrupts",   /* Interrupt usage */
    "/proc/ioports",      /* I/O port regions */
    "/proc/meminfo",      /* Memory statistics */
    "/proc/version",      /* Kernel version */
    "/proc/scsi/scsi"     /* SCSI device information */
};

/**
 * Read and display information from a /proc file
 * 
 * @param inf Index into the info[] array specifying which file to read
 */
void get_info(int inf) {
    FILE *fp;
    char buffer[BUF];
    size_t bytes_read;

    /* Open the requested /proc file */
    fp = fopen(info[inf], "r");
    if (fp == NULL) {
        perror("fopen()");
        printf("Press ENTER to continue");
        getchar();
        return;
    }

    /* Read file contents into buffer */
    bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    if (bytes_read == 0) {
        printf("No data read from file\n");
        printf("Press ENTER to continue");
        getchar();
        return;
    }

    /* Null-terminate and display the buffer */
    buffer[bytes_read] = '\0';
    printf("\n%s\n", buffer);
    printf("Press ENTER to continue");
    getchar();
}

/**
 * Main menu loop for viewing system information
 * 
 * Displays a menu of system information categories and allows the user
 * to select which information to view from the /proc filesystem.
 */
int main(void) {
    int choice;

    do {
        /* Display menu */
        printf("\n=== System Information Menu ===\n");
        printf("-%d- Processor Information\n", CPU);
        printf("-%d- Devices\n", DEV);
        printf("-%d- DMA Channels\n", DMA);
        printf("-%d- Interrupts\n", INT);
        printf("-%d- I/O Ports\n", IOP);
        printf("-%d- Memory Information\n", MEM);
        printf("-%d- Kernel Version\n", VERS);
        printf("-%d- SCSI Devices\n", SCSI);
        printf("-%d- Exit\n", EXIT);
        printf("\nYour choice: ");

        /* Read user input */
        do { 
            scanf("%d", &choice); 
        } while (getchar() != '\n');

        /* Process user selection */
        switch (choice) {
            case CPU:  get_info(CPU);  break;
            case DEV:  get_info(DEV);  break;
            case DMA:  get_info(DMA);  break;
            case INT:  get_info(INT);  break;
            case IOP:  get_info(IOP);  break;
            case MEM:  get_info(MEM);  break;
            case VERS: get_info(VERS); break;
            case SCSI: get_info(SCSI); break;
            case EXIT: printf("Goodbye!\n"); break;
            default:   printf("Invalid input. Please try again.\n");
        }
    } while (choice != EXIT);

    return EXIT_SUCCESS;
}
