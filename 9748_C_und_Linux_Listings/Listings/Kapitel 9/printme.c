/* printme.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF 8192

void an_den_drucker (char *text) {
	FILE *p;
	/* Pipe zum Tool lpr erstellen zum Schreiben auf lpr */
	p = popen ("lpr", "w");
	if (p == NULL) {
		perror("popen()");
		exit (EXIT_FAILURE);
	}
	/* an den Drucker schreiben */
	printf ("Sende Auftrag an den Drucker ...\n");
	fprintf (p, "%s", text);
	fflush (p);
	pclose (p);
	return;
}

int main (void) {
	char puffer[BUF], inhalt[BUF];
	inhalt[0] = '\0';
	printf ("Bitte Text zum Drucken schreiben "
		" (Beenden mit STRG+D)!\n-> ");
	while (fgets (puffer, BUF, stdin) != NULL) {
		if( strlen(inhalt) + strlen(puffer) < BUF ) {
			strcat (inhalt, puffer);
			printf ("->");
		}
		else
			break;
	}
	inhalt[BUF] = '\0';

	an_den_drucker (inhalt);
	return EXIT_SUCCESS;
}
