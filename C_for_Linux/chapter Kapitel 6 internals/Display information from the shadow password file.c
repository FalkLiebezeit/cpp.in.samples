/**
 * read_shadow.c - Display information from the shadow password file
 * 
 * This program demonstrates access to the shadow password database (/etc/shadow)
 * which contains secure password information and account aging details.
 * 
 * *** REQUIRES ROOT/SUPERUSER PRIVILEGES ***
 * 
 * The shadow file is only readable by root for security reasons. This program
 * shows how to iterate through shadow entries and extract:
 * - Encrypted password hash
 * - Password aging information (last change, min/max days, warnings, etc.)
 * - Account expiration settings
 * 
 * Security Note: Handle shadow information carefully - never display or log
 * password hashes in production systems.
 */

#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <string.h>
#include <time.h>

/**
 * Manually search for a user in the shadow password database
 * 
 * Iterates through all shadow entries using getspent() to find a specific user.
 * Similar to getspnam() but demonstrates manual iteration.
 * 
 * @param username Username to search for
 * @return Pointer to spwd structure if found, NULL otherwise
 * 
 * @note Requires root privileges to access shadow database
 * @note Properly closes database with endspent() in all code paths
 */
static struct spwd *getshadow(const char *username) {
	struct spwd *entry;

	/* Iterate through all shadow password entries */
	while ((entry = getspent()) != NULL) {
		/* Check if this entry matches the requested username */
		if (strcmp(entry->sp_namp, username) == 0) {
			endspent();  /* Close shadow database */
			return entry;
		}
	}
	
	/* User not found - close database and return NULL */
	endspent();
	return NULL;
}

/**
 * Convert days since epoch to human-readable date
 * 
 * @param days Days since Unix epoch (Jan 1, 1970)
 * @return Static string containing formatted date
 */
static const char *days_to_date(long days) {
	static char buffer[64];
	time_t timestamp;
	struct tm *timeinfo;
	
	if (days <= 0) {
		return "Never";
	}
	
	/* Convert days to seconds since epoch */
	timestamp = days * 86400;  /* 24 * 60 * 60 */
	timeinfo = localtime(&timestamp);
	
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
	return buffer;
}

/**
 * Main entry point
 * 
 * @param argc Argument count
 * @param argv Argument vector (expects username as argv[1])
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[]) {
	struct spwd *shadow_info;

	/* Validate command-line arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s USERNAME\n", argv[0]);
		fprintf(stderr, "Display shadow password information for a user.\n");
		fprintf(stderr, "\n*** REQUIRES ROOT PRIVILEGES ***\n");
		return EXIT_FAILURE;
	}

	/* Look up user in shadow database */
	shadow_info = getshadow(argv[1]);
	if (shadow_info == NULL) {
		fprintf(stderr, "Error: Could not find user '%s' in shadow database\n", argv[1]);
		fprintf(stderr, "Possible causes:\n");
		fprintf(stderr, "  - User does not exist\n");
		fprintf(stderr, "  - Insufficient privileges (need root access)\n");
		fprintf(stderr, "  - Shadow passwords not enabled on this system\n");
		return EXIT_FAILURE;
	}

	/* Display shadow password information */
	printf("\n=== Shadow Password Information for '%s' ===\n\n", argv[1]);
	printf("Username              : %s\n", shadow_info->sp_namp);
	printf("Encrypted Password    : %s\n", 
	       shadow_info->sp_pwdp ? shadow_info->sp_pwdp : "(none)");
	
	/* Password aging information (in days since Jan 1, 1970) */
	printf("\n--- Password Aging Policy ---\n");
	printf("Last Password Change  : %ld days since epoch (%s)\n",
	       shadow_info->sp_lstchg, days_to_date(shadow_info->sp_lstchg));
	printf("Min Days Between Changes: %ld days\n", shadow_info->sp_min);
	printf("Max Days Before Change  : %ld days\n", shadow_info->sp_max);
	printf("Warning Period        : %ld days before expiration\n", shadow_info->sp_warn);
	printf("Inactivity Period     : %ld days after expiration\n", shadow_info->sp_inact);
	printf("Account Expiration    : %ld days since epoch (%s)\n",
	       shadow_info->sp_expire, days_to_date(shadow_info->sp_expire));
	printf("\n");

	return EXIT_SUCCESS;
}
