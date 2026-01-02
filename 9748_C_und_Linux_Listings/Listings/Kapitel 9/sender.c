/* sender.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF 4096

int main (void) {
	char puffer[BUF], inhalt[BUF];
	int fd;

	inhalt[0] = '\0';
	/* Der Sender schreibt nur in die FIFO. */
	fd = open ("fifo1.1", O_WRONLY);
	if (fd == -1) {
		perror ("open()");
		exit (EXIT_FAILURE);
	}
	printf ("Bitte geben Sie Ihre Nachricht für die FIFO ein"
		" (Mit STRG+D beenden)\n>");
	while (fgets (puffer, BUF, stdin) != NULL) {
		if( strlen(inhalt) + strlen(puffer) < BUF ) {
			strcat (inhalt, puffer);
			printf (">");
		}
		else
			break;
	}
	inhalt[BUF] = '\0';
	write (fd, inhalt, strlen (inhalt) + 1);
	return EXIT_SUCCESS;
}
