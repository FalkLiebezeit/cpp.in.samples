/* server.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF 4096
#define TEXT "Habe Ihre Anfrage soeben erhalten\n"

void an_den_drucker (char *text) {
	FILE *p;
	/* Pipe zum Tool lpr erstellen zum Schreiben auf lpr */
	p = popen ("lpr", "w");
	if (p == NULL) {
		perror ("popen()");
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
	char puffer[BUF], inhalt[BUF], antwort[BUF], pid[6];
	int r_fd, w_fd, n, i;

	inhalt[0] = '\0';
	/* alle Zugriffsrechte der Dateikreierungsmaske erlauben */
	umask(0);
	if (mkfifo ("fifo1.1", O_RDWR | 0666) < 0) {
		/* FIFO bereits vorhanden - kein fataler Fehler */
		if(errno == EEXIST)
			printf ("Versuche, vorhandene FIFO zu verwenden\n");
		else {
			perror("mkfifio()");
			exit (EXIT_FAILURE);
		}
	}
	/* Empfänger liest nur aus der FIFO. */
	r_fd = open ("fifo1.1", O_RDONLY);
	if (r_fd == -1) {
		perror ("open(1)");
		exit (EXIT_FAILURE);
	}
	while (1) { /* Endlosschleife */
		if (read (r_fd, puffer, BUF) != 0) {
			an_den_drucker (puffer);
			/* PID des aufrufenden Prozesses ermitteln */
			n = 0, i = 0;
			while (puffer[n] != '\n')
				pid[i++] = puffer[n++];
			pid[++i] = '\n';
			strcpy (antwort, "fifo.");
			strncat (antwort, pid, i);
			w_fd = open (antwort, O_WRONLY);
			if (w_fd == -1) {
				perror ("open(2)");
				exit (EXIT_FAILURE);
		}
		write (w_fd, TEXT, sizeof(TEXT));
		close (w_fd);
	}
	sleep(1);
	}
	return EXIT_SUCCESS;
}
