/**
 * passwortinfo2.c - Display user account information using manual database iteration
 * 
 * This program demonstrates an alternative approach to querying user information
 * by manually iterating through the entire password database using getpwent().
 * 
 * Key differences from passwortinfo.c:
 * - Uses getpwent() to iterate through all entries instead of getpwnam()
 * - Demonstrates sequential password database access
 * - Shows proper cleanup with endpwent()
 * 
 * Note: This approach is less efficient than getpwnam() for single lookups,
 * but useful for understanding database iteration or when processing all users.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

/**
 * Manually search for a user by iterating through the password database
 * 
 * This function demonstrates sequential access to the password database,
 * which is typically handled automatically by getpwnam().
 * 
 * @param username Username to search for
 * @return Pointer to passwd structure if found, NULL otherwise
 * 
 * @note Less efficient than getpwnam() for single user lookups
 * @note Properly closes database with endpwent() in all code paths
 */
static struct passwd *getpasswd(const char *username) {
	struct passwd *entry;

	/* Iterate through all password database entries */
	while ((entry = getpwent()) != NULL) {
		/* Check if this entry matches the requested username */
		if (strcmp(entry->pw_name, username) == 0) {
			endpwent();  /* Close database before returning */
			return entry;
		}
	}
	
	/* User not found - close database and return NULL */
	endpwent();
	return NULL;
}

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
		fprintf(stderr, "Display user information by iterating through password database.\n");
		return EXIT_FAILURE;
	}

	/* Look up user using custom iteration function */
	user_info = getpasswd(argv[1]);
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
