/* fifo4.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define FIFO "/tmp/fifo0001.1"

int main (void) {
	int r_fifo, w_fifo;
	char puffer[] =
		"Der Text für die FIFO an den Elternprozess\n";
	char buf[100];
	pid_t pid;

	if ((mkfifo (FIFO, S_IRUSR | S_IWUSR)) == -1) {
		/* FIFO bereits vorhanden - kein fataler Fehler */
		if(errno == EEXIST)
			perror ("mkfifo()");
		else {
			perror("mkfifio()");
			exit (EXIT_FAILURE);
		}
	}
	pid = fork ();
	if (pid == -1) {
		perror ("fork()");
		exit (EXIT_FAILURE);
	}
	else if (pid > 0) { /* Elternprozess liest aus der FIFO. */
		if ((r_fifo = open (FIFO, O_RDONLY)) < 0) {
			perror ("open()");
			exit (EXIT_FAILURE);
		}
		/* Wir warten auf das Ende des Kindprozesses. */
		while (wait (NULL) != pid);
		/* Lesen aus der FIFO */
		read (r_fifo, buf, strlen (puffer));
		buf[strlen(puffer)] = '\0';
		printf(" --- Elternprozess ---\n");
		printf ("%s", buf);
		close (r_fifo);
	}
	else { /* Kindprozess schreibt in die FIFO */
		printf(" --- Kindprozess ---\n");
		if ((w_fifo = open (FIFO, O_WRONLY)) < 0) {
			perror ("open()");
			exit (EXIT_FAILURE);
		}
		/* Schreiben in die FIFO */
		write (w_fifo, puffer, strlen (puffer));
		close (w_fifo); /* EOF */
		exit (EXIT_SUCCESS);
	}
	printf(" --- Ende ---\n");
	return EXIT_SUCCESS;
}
