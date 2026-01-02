/* client.c */
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
	char puffer[BUF], inhalt[BUF], delete_fifo[BUF];
	int fd, fdx;

	sprintf (puffer, "fifo.%d", getpid ());
	inhalt[0] = '\0';
	/* Erste Zeile der Nachricht enthält die PID. */ 
	sprintf (inhalt, "%d\n", getpid ());

	/* alle Zugriffsrechte der Dateikreierungsmaske erlauben */
	umask(0);
	if (mkfifo (puffer, O_RDWR | 0666) < 0) {
		/* FIFO bereits vorhanden - kein fataler Fehler */
		if(errno == EEXIST)
			printf ("Versuche, vorhandene FIFO zu verwenden\n");
		else {
			perror("mkfifio()");
			exit (EXIT_FAILURE);
		}
	}
	fd = open ("fifo1.1", O_WRONLY);
	fdx = open (puffer, O_RDWR);
	if (fd == -1 || fdx == -1) {
		perror ("open()");
		exit (EXIT_FAILURE);
	}

	strcmp (delete_fifo, puffer);
	printf ("Bitte geben Sie Ihre Nachricht ein"
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
	write (fd, inhalt, BUF);
	if (read (fdx, puffer, BUF))
		printf ("%s\n", puffer);
	/* Antwort-FIFO wieder löschen */
	unlink (delete_fifo);
	return EXIT_SUCCESS;
}
