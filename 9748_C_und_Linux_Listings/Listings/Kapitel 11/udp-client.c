/* udp-client.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#define SERVER_PORT 1234

int main (int argc, char **argv) {
	int s, rc, i;
	struct sockaddr_in cliAddr, remoteServAddr;
	struct hostent *h;

	/* Kommandozeile auswerten */
	if (argc < 3) {
		printf ("Usage: %s <server> <data1> ... <dataN> \n",
			argv[0] );
		exit (EXIT_FAILURE);
	}
	/* IP-Adresse desvom Server s überprüfen */
	h = gethostbyname (argv[1]);
	if (h == NULL) {
		printf ("%s: unbekannter Host '%s' \n",
			argv[0], argv[1] );
		exit (EXIT_FAILURE);
	}
	printf ("%s: sende Daten an '%s' (IP : %s) \n",
		argv[0], h->h_name,
		inet_ntoa (*(struct in_addr *) h->h_addr_list[0]) );
	remoteServAddr.sin_family = h->h_addrtype;
	memcpy ( (char *) &remoteServAddr.sin_addr.s_addr,
		h->h_addr_list[0], h->h_length);
	remoteServAddr.sin_port = htons (SERVER_PORT);

	/* Socket erzeugen */
	s = socket (AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		printf ("%s: Kann Socket nicht öffnen (%s) \n",
			argv[0], strerror(errno));
		exit (EXIT_FAILURE);
	}
	/* Jeden jeden Port bind(en) */
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	cliAddr.sin_port = htons (0);
	rc = bind ( s, (struct sockaddr *) &cliAddr,
			sizeof (cliAddr) );
	if (rc < 0) {
		printf ("%s: Konnte Port nicht bind(en) (%s)\n",
			argv[0], strerror(errno));
		exit (EXIT_FAILURE);
	}
	/* Daten senden */
	for (i = 2; i < argc; i++) {
		rc = sendto (s, argv[i], strlen (argv[i]) + 1, 0,
			(struct sockaddr *) &remoteServAddr,
			sizeof (remoteServAddr));
		if (rc < 0) {
			printf ("%s: Konnte Daten nicht senden %d\n",
				argv[0], i-1 );
			close (s);
			exit (EXIT_FAILURE);
		}
	}
	return EXIT_SUCCESS;
}
