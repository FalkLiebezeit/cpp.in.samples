/* memory.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

long int get_mem_total (void) {
	FILE *fp;
	char buffer[1024];
	size_t bytes_read;
	char *match;
	long mem_tot;

	if((fp = fopen("/proc/meminfo", "r")) == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);
	if (bytes_read == 0 || bytes_read == sizeof (buffer))
		return 0;
	buffer[bytes_read] = '\0';
	/* Suchen nach der Stringfolge "MemTotal" */
	match = strstr (buffer, "MemTotal");
	if (match == NULL) /* nicht gefunden */
		return 0;
	sscanf (match, "MemTotal: %ld", &mem_tot);
	return (mem_tot/1024); /* 1 MB = 1024 KB */
}

int main (void) {
	long memory = get_mem_total();
	if(memory == 0)
		printf("Konnte RAM nicht ermitteln\n");
	else
		printf("Vorhandener Arbeitsspeicher: %ld MB\n" ,memory);
	return EXIT_SUCCESS;
}
