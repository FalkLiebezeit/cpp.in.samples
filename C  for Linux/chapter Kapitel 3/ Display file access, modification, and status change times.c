/* file_times.c - Display file access, modification, and status change times */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

/**
 * file_times() - Display file timestamp information
 * @name: path to the file to query
 * 
 * Retrieves and displays three timestamps:
 * - Last access time (atime): when file was last read
 * - Last modification time (mtime): when file content was last changed
 * - Last status change time (ctime): when file metadata was last changed
 * 
 * Returns: 0 on success, -1 on error
 */
int file_times(const char *name) {
	struct stat st;
	
	// Validate input parameter
	if(name == NULL) {
		fprintf(stderr, "Error: NULL filename provided\n");
		return -1;
	}
	
	// Retrieve file statistics
	if(stat(name, &st) < 0) {
		fprintf(stderr, "Error in stat(): %s\n", strerror(errno));
		return -1;
	}
	
	// Display all three timestamps
	printf("Last access time         : %s", ctime(&st.st_atime));
	printf("Last modification time   : %s", ctime(&st.st_mtime));
	printf("Last status change time  : %s", ctime(&st.st_ctime));
	
	return 0;
}

int main(int argc, char **argv) {
	// Check command line arguments
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// Query and display file timestamps
	if(file_times(argv[1]) < 0) {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
