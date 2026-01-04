/**
 * read_shadow2.c - Display shadow password information using direct lookup
 * 
 * This program demonstrates the preferred method for accessing shadow password
 * information using getspnam() instead of manual iteration with getspent().
 * 
 * *** REQUIRES ROOT/SUPERUSER PRIVILEGES ***
 * 
 * Key differences from read_shadow.c:
 * - Uses getspnam() for direct lookup (more efficient)
 * - No manual iteration through database
 * - Simpler implementation for single-user queries
 * 
 * The shadow file (/etc/shadow) contains:
 * - Encrypted password hashes
 * - Password aging information
 * - Account expiration settings
 * 
 * Security Note: Shadow file access requires root privileges. Handle this
 * sensitive information carefully.
 */

#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <string.h>
#include <time.h>

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

	/* Direct lookup in shadow database using getspnam() */
	shadow_info = getspnam(argv[1]);
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
	printf("Max Days Before Change  : %ld days", shadow_info->sp_max);
	if (shadow_info->sp_max > 0) {
		printf(" (password expires %ld days after change)\n", shadow_info->sp_max);
	} else {
		printf(" (no maximum, password never expires)\n");
	}
	printf("Warning Period        : %ld days before expiration\n", shadow_info->sp_warn);
	printf("Inactivity Period     : %ld days after expiration before account locks\n", 
	       shadow_info->sp_inact);
	printf("Account Expiration    : %ld days since epoch (%s)\n",
	       shadow_info->sp_expire, days_to_date(shadow_info->sp_expire));
	printf("\n");

	return EXIT_SUCCESS;
}
