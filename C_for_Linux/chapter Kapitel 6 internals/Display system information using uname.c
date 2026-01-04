/**
 * utsname.c - Display system information using uname()
 * 
 * This program demonstrates the use of the uname() system call to retrieve
 * comprehensive information about the current system, including:
 * - Operating system name
 * - Network node hostname
 * - OS release version
 * - OS version/build information
 * - Hardware architecture
 * - Domain name (GNU extension)
 * 
 * The uname() function populates a utsname structure with system identification
 * information. This is similar to the 'uname' command-line utility.
 */

#define _GNU_SOURCE  /* Enable GNU extensions for domainname field */

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

/**
 * Main entry point
 * 
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(void) {
	struct utsname system_info;

	/* Retrieve system information using uname() */
	if (uname(&system_info) < 0) {
		perror("uname");
		fprintf(stderr, "Error: Failed to retrieve system information\n");
		return EXIT_FAILURE;
	}

	/* Display system information */
	printf("\n=== System Information (uname) ===\n\n");
	printf("Operating System: %s\n", system_info.sysname);
	printf("Hostname        : %s\n", system_info.nodename);
	printf("OS Release      : %s\n", system_info.release);
	printf("OS Version      : %s\n", system_info.version);
	printf("Architecture    : %s\n", system_info.machine);
	
	/* Domain name is a GNU extension */
	#ifdef _GNU_SOURCE
	printf("Domain Name     : %s\n", system_info.domainname);
	#endif
	
	printf("\n");

	return EXIT_SUCCESS;
}
