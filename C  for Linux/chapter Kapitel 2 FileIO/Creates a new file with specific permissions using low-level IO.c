/* make_file.c 
 * Creates a new file with specific permissions using low-level I/O
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	// File permissions for the new file: -rw-rw-r-- (owner: rw, group: rw, others: r)
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	int fd; // File descriptor
	
	// Check if filename argument is provided
	if (argc < 2 || argv[1] == NULL) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	// Allow all permissions (disable umask restrictions)
	umask(0);
	
	/* Create a new file with the following flags:
	 * O_WRONLY - Open for writing only
	 * O_CREAT  - Create file if it doesn't exist
	 * O_EXCL   - Fail if file already exists (ensures we don't overwrite)
	 * mode     - Set file permissions
	 */
	fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, mode);
	if (fd == -1) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	
	// Close the file descriptor before exiting
	close(fd);
	
	printf("File '%s' created successfully with permissions -rw-rw-r--\n", argv[1]);
	return EXIT_SUCCESS;
}
