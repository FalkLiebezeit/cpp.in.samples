/* pserver.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define  MAX_ZEICHEN 16384
#define  PORT_NUMMER  1234

typedef void (*sighandler_t)(int);

static sighandler_t
my_signal(int sig_nr, sighandler_t signalhandler) {
	struct sigaction neu_sig, alt_sig;

	neu_sig.sa_handler = signalhandler;
	sigemptyset (&neu_sig.sa_mask);
	neu_sig.sa_flags = SA_RESTART;
	if (sigaction (sig_nr, &neu_sig, &alt_sig) < 0)
		return SIG_ERR;
	return alt_sig.sa_handler;
}

static void no_zombie (int signr) {
	pid_t pid;
	int ret;

	while ((pid = waitpid (-1, &ret, WNOHANG)) > 0)
		printf ("Child-Server mit pid=%d hat sich beendet\n",
			pid );
	return;
}

int main (void) {
	int sockfd, connfd, fd, j, n, ngesamt;
	struct sockaddr_in adresse;
	const int y = 1;
	size_t adrlaenge = sizeof (struct sockaddr_in);

	char puffer[MAX_ZEICHEN];
	char path_file[MAX_ZEICHEN];
	pid_t pid;

	if ((sockfd = socket (PF_INET, SOCK_STREAM, 0)) < 0) {
		printf ("Fehler bei socket() ...(%s)\n",
			strerror(errno));
		exit (EXIT_FAILURE);
	}
	printf ("Socket erfolgreich angelegt\n");
	adresse.sin_family = AF_INET;
	adresse.sin_port = htons (PORT_NUMMER);
	memset (&adresse.sin_addr, 0, sizeof (adresse.sin_addr));

	setsockopt( sockfd, SOL_SOCKET,
		SO_REUSEADDR, &y, sizeof(int) );

	if (bind ( sockfd,
		(struct sockaddr *) &adresse,
		sizeof (adresse) ) ) {
		printf ("Fehler bei bind() ...(%s)\n",
			strerror(errno));
		exit (EXIT_FAILURE);
	}
	printf ("Server ist bereit und wartet ...\n");
	if (listen (sockfd, 5) ) {
		printf ("Fehler bei listen() ...(%s)\n",
			strerror(errno));
		exit (EXIT_FAILURE);
	}
	my_signal (SIGCHLD, no_zombie);

	while(1) {
		connfd = accept ( sockfd,
			(struct sockaddr *) &adresse,
			&adrlaenge );
		if( connfd < 0 ) {
			if( errno == EINTR )
				continue;
			else {
				printf("Fehler bei accept() (%s)\n",
					strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		printf (" ...  Daten empfangen\n");

		/* Neuen neuen Kindprozess-Server starten */
		if ((pid = fork ()) == 0) {
			close (sockfd);
			/* Dateiname */
			j = 0;
			while ((n = read (connfd, &puffer[j], 1)) > 0) {
				if (puffer[j] == '\n') {
					puffer[j] = 0;
					break;
				}
				j++;
			}
			if (n < 0) {
				printf ("Fehler bei read() ...\n");
				exit (EXIT_FAILURE);
			}
			printf("(%d): Dateiname \"%s\"  wird kopiert nach ",
				getpid(),puffer);
			strcpy (path_file, getenv ("HOME"));
			strcat (path_file, "/tmp/");
			strcat (path_file, puffer);
			printf ("%s\n", path_file);

			/* Datei zum Lesen öffnen */
			if ((fd = open ( path_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644 ) ) < 0 ) {
				printf ("... kann %s nicht öffnen\n", puffer);
				close (connfd);
				continue;
			}
			/* Datei aus dem Socket lesen und in lokale */
			/*  Kopie schreiben                         */
			ingesamt = 0;
			while((n=read(connfd, puffer, sizeof (puffer)))>0) {
				if (write (fd, puffer, n) != n) {
					printf ("Fehler bei write() ...\n");
					exit (EXIT_FAILURE);
				}
				ingesamt += n;
			}
			if (n < 0) {
				printf ("Fehler bei read() ...\n");
				exit (EXIT_FAILURE);
			}
			printf ("...  beendet (%d Bytes)\n", ingesamt);
			close (fd);
			exit(EXIT_SUCCESS);
			/* Ende Kindprozess */
		} // Ende fork()
		close (connfd);
	}// Ende while(1)
	close (sockfd);
	exit (EXIT_SUCCESS);
}
