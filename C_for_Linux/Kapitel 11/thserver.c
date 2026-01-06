/* thserver.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#define  MAX_ZEICHEN  16384
#define  PORT_NUMMER  1234

static void * threading_socket( void *);
static void copy (int);

pthread_t th;

static void *threading_socket (void *arg) {
	pthread_detach (pthread_self ());
	copy ((int) arg);
	close ((int) arg);
	return NULL;
}

static void copy (int connfd) {
	int  fd;
	ssize_t j, n, ngesamt;
	char puffer[MAX_ZEICHEN];
	char path_file[MAX_ZEICHEN];

	printf (" ... Daten empfangen\n");
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

	printf ("Dateiname \"%s\"  wird kopiert nach ", puffer);
	strcpy (path_file, getenv ("HOME"));
	strcat (path_file, "/tmp/");
	strcat (path_file, puffer);
	printf ("%s\n", path_file);

	/* Datei zum Lesen öffnen */
	if ((fd = open ( path_file,
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
		printf ("... kann %s nicht öffnen (%s)\n",
			puffer, strerror(errno));
		close (connfd);
	}
	/* Datei aus dem Socket lesen und in lokale Kopie schreiben */
	ngesamt = 0;
	while ((n = read (connfd, puffer, sizeof (puffer))) > 0) {
		if (write (fd, puffer, n) != n) {
			printf ("Fehler bei write() ...(%s)\n",
				strerror(errno));
			exit (EXIT_FAILURE);
		}
		ingesamt += n;
	}
	if (n < 0) {
		printf ("Fehler bei read() ...\n");
	}
	printf ("... beendet (%d Bytes)\n", ingesamt);
	close (fd);
	close (connfd);
	return;
}

int main (void) {
	int sockfd, connfd;
	struct sockaddr_in adresse;
	size_t adrlaenge = sizeof (struct sockaddr_in);
	const int y = 1;

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
		SO_REUSEADDR, &y, sizeof(int));

	if (bind ( sockfd,
		(struct sockaddr *) &adresse,
		sizeof (adresse) ) ) {
		printf ("Fehler bei bind() ...(%s)\n",
			strerror(errno));
		exit (EXIT_FAILURE);
	}
	printf ("Server ist bereit und wartet ...\n");

	if (listen (sockfd, 5)) {
		printf ("Fehler bei listen() ...(%s)\n",
			strerror(errno));
		exit (EXIT_FAILURE);
	}
	while (1) {
		connfd = accept ( sockfd,
			(struct sockaddr *) &adresse,
			&adrlaenge );
		if (connfd < 0) {
			if (errno == EINTR)
				continue;
			else {
				printf ("Fehler bei accept() ...\n");
				exit (EXIT_FAILURE);
			}
		}
		pthread_create(&th, NULL, &threading_socket, connfd);
	}
	exit (EXIT_SUCCESS);
}
