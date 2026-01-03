/* filesize-Demo.c - Demonstrate retrieving file size using stat() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * filesize() - Display the size of a file
 * @name: path to the file to query
 * 
 * Uses the stat() system call to retrieve file information
 * and displays the file size in bytes.
 * 
 * Returns: 0 on success, -1 on error
 */
int filesize(const char *name) {
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
	
	// Display file size (using long long for large files)
	printf("File size (st_size): %lld bytes\n", (long long)st.st_size);
	
	return 0;
}

int main(int argc, char **argv) {
	// Check command line arguments
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// Query and display file size
	if(filesize(argv[1]) < 0) {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
