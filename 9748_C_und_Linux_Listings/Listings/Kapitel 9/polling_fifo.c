/* polling_fifo.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define BUF 4096

void an_den_drucker (char *text) { // kein static für CUPS
	FILE *p;
	/* Pipe zum Tool lpr erstellen zum Schreiben auf lpr */
	p = popen ("lpr", "w");
	// evtl. für USB anpassen:
	// p = popen ("/usb/lp0", "w"); oder
	// p = popen ("/prnusb/lpr", "w"); (Pi ab V2 setzt eventuell diesen Link.)
	if (p == NULL) {
		perror ("popen()");
		exit (EXIT_FAILURE);
	}
	/* an den Drucker schreiben */
	printf ("Sende Auftrag an den Drucker ...\n");
	fprintf (p, "%s", text);
	pclose (p);
}

int main (void) {
	char puffer[BUF], inhalt[BUF];
	int fd;

	inhalt[0] = '\0';
	umask(0);
	if (mkfifo ("fifo1.1", 0666) < 0) {
		/* FIFO bereits vorhanden - kein fataler Fehler */
		if(errno == EEXIST)
			printf ("Versuche, vorhandene FIFO zu verwenden\n");
		else {
			perror("mkfifio()");
			exit (EXIT_FAILURE);
		}
	}
	/* Empfänger liest nur aus der FIFO. */
	fd = open ("fifo1.1", O_RDONLY);
	if (fd == -1) {
		perror ("open()");
		exit (EXIT_FAILURE);
	}
	while (1) { /* Endlosschleife */
		if ( read (fd, puffer, BUF) )
			an_den_drucker (puffer);
			sleep (2);
	}
	return EXIT_SUCCESS;
}

