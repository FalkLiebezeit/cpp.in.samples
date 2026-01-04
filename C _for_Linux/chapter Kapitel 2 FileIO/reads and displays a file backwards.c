/* backward.c
 * Reads and displays a file backwards (from end to beginning)
 * Demonstrates file seeking with lseek() and reading in reverse
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Read file backwards and print to stdout
 * fd - file descriptor of the file to read
 */
void bwread(int fd) {
	int rv;
	int nl = 0; // Flag to track if we've seen a newline
	char ch;

	// Seek to last character in file (one byte before end)
	if (lseek(fd, -1, SEEK_END) < 0) {
		fprintf(stderr, "Error: File is empty or seek failed\n");
		return;
	}

	// Read file backwards one character at a time
	while ((rv = read(fd, &ch, 1)) == 1) {
		// Skip the first newline at end of file
		if (ch == '\n' && !nl) {
			++nl;
		} else {
			putc(ch, stdout);
		}
		
		// Move back 2 positions: -1 to undo the read, -1 to move to previous char
		if (lseek(fd, -2, SEEK_CUR) < 0) {
			break; // Reached beginning of file
		}
	}

	// Add newline at the end if we skipped one at the beginning
	if (nl) {
		putc('\n', stdout);
	}

	// Check for errors
	if (rv == 0) {
		fprintf(stderr, "Unexpected EOF...\n");
	} else if (rv == -1) {
		perror("Error reading file");
	}
}

int main(int argc, char **argv) {
	int fd;

	// Check for correct command line arguments
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Open file for reading
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("Error opening file");
		return EXIT_FAILURE;
	}
	
	// Read and display file backwards
	bwread(fd);

	// Close file descriptor
	close(fd);

	return EXIT_SUCCESS;
}
