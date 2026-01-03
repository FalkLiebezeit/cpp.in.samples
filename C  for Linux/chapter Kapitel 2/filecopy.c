/* filecopy.c - Efficient file copying utility using low-level I/O */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCKSIZE 4096  // Optimal buffer size (4KB) for most filesystems

/**
 * write2() - Wrapper for write() that handles partial writes
 * @fd: file descriptor to write to
 * @buf: buffer containing data to write
 * @count: number of bytes to write
 * 
 * Returns: number of bytes written on success, -1 on error
 */
static ssize_t write2(int fd, const void *buf, size_t count) {
	size_t bytes_written = 0;
	ssize_t result;
	const char *ptr = (const char *)buf;
	
	// Loop until all bytes are written
	while(bytes_written < count) {
		result = write(fd, ptr + bytes_written, count - bytes_written);
		if(result < 0) {
			return -1;  // Error occurred
		}
		bytes_written += result;
	}
	return bytes_written;
}

int main(int argc, char **argv) {
	// File permissions for the new file: -rw-rw-r-- (664)
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	char buffer[BLOCKSIZE];
	int fd_r, fd_w;  // File descriptors for read and write
	ssize_t n;
	int exit_code = EXIT_SUCCESS;

	// Allow all permissions (umask won't restrict)
	umask(0);

	// Check command line arguments
	if(argc < 3) {
		fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Open source file for reading
	fd_r = open(argv[1], O_RDONLY);
	if(fd_r == -1) {
		perror("Error opening source file");
		return EXIT_FAILURE;
	}

	// Open destination file for writing (create new, fail if exists)
	fd_w = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, mode);
	if(fd_w == -1) {
		perror("Error opening destination file");
		close(fd_r);
		return EXIT_FAILURE;
	}

	// Copy data in blocks
	while((n = read(fd_r, buffer, BLOCKSIZE)) > 0) {
		if(write2(fd_w, buffer, n) < 0) {
			perror("Error writing to destination file");
			exit_code = EXIT_FAILURE;
			break;
		}
	}

	// Check for read errors
	if(n < 0) {
		perror("Error reading from source file");
		exit_code = EXIT_FAILURE;
	}

	// Close file descriptors
	if(close(fd_r) < 0) {
		perror("Error closing source file");
		exit_code = EXIT_FAILURE;
	}
	if(close(fd_w) < 0) {
		perror("Error closing destination file");
		exit_code = EXIT_FAILURE;
	}

	return exit_code;
}
