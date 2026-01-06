/**
 * groupname.c - Display detailed information about a Unix/Linux group
 * 
 * This program queries the system group database and displays comprehensive
 * information about a specified group, including:
 * - Group name
 * - Encrypted password (if any)
 * - Group ID (GID)
 * - List of all group members
 * 
 * Uses the getgrnam() function to retrieve group information from /etc/group
 * and related system databases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <grp.h>

/**
 * Main entry point
 * 
 * @param argc Argument count
 * @param argv Argument vector (expects group name as argv[1])
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[]) {
	struct group *group_info;
	int member_index = 0;

	/* Validate command-line arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s GROUP_NAME\n", argv[0]);
		fprintf(stderr, "Display detailed information about a system group.\n");
		return EXIT_FAILURE;
	}

	/* Query group database by name */
	group_info = getgrnam(argv[1]);
	if (group_info == NULL) {
		fprintf(stderr, "Error: Could not find group '%s'\n", argv[1]);
		fprintf(stderr, "The group may not exist or you may lack read permissions.\n");
		return EXIT_FAILURE;
	}

	/* Display group information */
	printf("\n=== Group Information for '%s' ===\n\n", argv[1]);
	printf("Group Name      : %s\n", group_info->gr_name);
	printf("Encrypted Password: %s\n", 
	       group_info->gr_passwd ? group_info->gr_passwd : "(none)");
	printf("Group ID (GID)  : %u\n", group_info->gr_gid);
	
	/* Display all group members */
	printf("\nGroup Members:\n");
	if (group_info->gr_mem[0] == NULL) {
		printf("  (no members listed)\n");
	} else {
		while (group_info->gr_mem[member_index] != NULL) {
			printf("  - %s\n", group_info->gr_mem[member_index]);
			member_index++;
		}
	}
	printf("\n");

	return EXIT_SUCCESS;
}
