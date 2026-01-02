/* pipe1. c */
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char **argv) {
	int fd[2], fd1, n;
	pid_t pid;
	char puffer[PIPE_BUF];

	if (argc != 2) {
		printf("Usage: %s Datei\n", *argv);
		exit (EXIT_FAILURE);
	}
	if ((fd1 = open (argv[1], O_RDONLY)) < 0) {
		perror ("open");
		exit (EXIT_FAILURE);
	}
	/* Wir erstellen eine Pipe. */
	if (pipe (fd) < 0) {
		perror ("pipe");
		exit (EXIT_FAILURE);
	}
	/* Wir erzeugen einen neuen Prozess. */
	if ((pid = fork ()) < 0) {
		perror ("fork");
		exit (EXIT_FAILURE);
	}
	else if (pid > 0) {   /* Elternprozess */
		close (fd[0]);   /* Leseseite schlieﬂen */
		/* Datei auslesen (PIPE_BUF Bytes) */
		n = read (fd1, puffer, PIPE_BUF);
		/* in die Schreibseite der Pipe schreiben */
		if ((write (fd[1], puffer, n)) != n) {
			perror ("write");
			exit (EXIT_FAILURE);
		}
		/* Warten auf den Kindprozess */
		if ((waitpid (pid, NULL, 0)) < 0) {
			perror ("waitpid");
			exit (EXIT_FAILURE);
		}
	}
	else { /* Kindprozess */
		close (fd[1]); /* Schreibseite schlieﬂen */
		/* Leseseite der Pipe auslesen (PIPE_BUF Bytes) */
		n = read (fd[0], puffer, PIPE_BUF);
		/* Daten auf Standardausgabe schreiben */
		if ((write (STDOUT_FILENO, puffer, n)) != n) {
			perror ("write");
			exit (EXIT_FAILURE);
		}
	}
	exit (EXIT_SUCCESS);
}
