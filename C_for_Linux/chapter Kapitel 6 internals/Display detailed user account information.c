/**
 * passwortinfo.c - Display detailed user account information
 * 
 * This program queries the system password database to retrieve and display
 * comprehensive information about a Unix/Linux user account, including:
 * - Username
 * - User ID (UID)
 * - Primary group ID (GID)
 * - User description/comment (GECOS field)
 * - Home directory
 * - Login shell
 * 
 * Uses getpwnam() to retrieve user information from /etc/passwd and related
 * system databases (including NIS, LDAP, etc. if configured).
 */

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

/**
 * Main entry point
 * 
 * @param argc Argument count
 * @param argv Argument vector (expects username as argv[1])
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[]) {
	struct passwd *user_info;

	/* Validate command-line arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s USERNAME\n", argv[0]);
		fprintf(stderr, "Display detailed information about a system user account.\n");
		fprintf(stderr, "\nAlternative: Use getpwuid() to query by UID instead.\n");
		return EXIT_FAILURE;
	}

	/* Query password database by username */
	/* Alternative approach using UID:
	 *   user_info = getpwuid(strtoul(argv[1], NULL, 10));
	 * This would look up the user by numeric UID instead of username.
	 */
	user_info = getpwnam(argv[1]);
	if (user_info == NULL) {
		fprintf(stderr, "Error: Could not find user '%s'\n", argv[1]);
		fprintf(stderr, "The user may not exist or you may lack read permissions.\n");
		return EXIT_FAILURE;
	}

	/* Display user account information */
	printf("\n=== User Account Information for '%s' ===\n\n", argv[1]);
	printf("Username        : %s\n", user_info->pw_name);
	printf("User ID (UID)   : %u\n", user_info->pw_uid);
	printf("Group ID (GID)  : %u\n", user_info->pw_gid);
	printf("User Description: %s\n", user_info->pw_gecos);
	printf("Home Directory  : %s\n", user_info->pw_dir);
	printf("Login Shell     : %s\n", user_info->pw_shell);
	printf("\n");

	return EXIT_SUCCESS;
}
