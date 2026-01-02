/* multi_client.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUF 1024

#define socket_t int

/* Funktion gibt aufgetretene Fehler aus und
* beendet die Anwendung. */
void error_exit(char *error_message) {
	fprintf(stderr, "%s: %s\n", error_message,
		strerror(errno));
	exit(EXIT_FAILURE);
}

int create_socket( int af, int type, int protocol ) {
	socket_t sock;
	const int y = 1;
	/* Erzeuge das Socket. */
	sock = socket(af, type, protocol);
	if (sock < 0)
		error_exit("Fehler beim Anlegen eines Sockets");
	setsockopt( sock, SOL_SOCKET,
		SO_REUSEADDR, &y, sizeof(int));
	return sock;
}

/* Baut die Verbindung zum Server auf. */
void connect_socket(socket_t *sock, char *serv_addr,
	unsigned short port) {
	struct sockaddr_in server;
	struct hostent *host_info;
	unsigned long addr;

	memset( &server, 0, sizeof (server));
	if ((addr = inet_addr( serv_addr )) != INADDR_NONE) {
		/* argv[1] ist eine nummerische IP-Adresse. */
		memcpy( (char *)&server.sin_addr,
			&addr, sizeof(addr));
	}
	else {
		/* Für den Fall der Fälle: Wandle den Servernamen,
		* z.B. "localhost", in eine IP-Adresse um. */
		host_info = gethostbyname( serv_addr );
		if (NULL == host_info)
			error_exit("Unbekannter Server");
		memcpy( (char *)&server.sin_addr, host_info->h_addr,
			host_info->h_length);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
	/* Baue die Verbindung zum Server auf. */
	if (connect( *sock, (struct sockaddr *)&server,
		sizeof( server)) < 0)
		error_exit( "Kann keine Verbindung zum Server "
			" herstellen");
}

/* Daten versenden via TCP */
void TCP_send( socket_t *sock, char *data, size_t size) {
	if(send( *sock, data, size, 0) == -1 )
		error_exit("Fehler bei send()");
}

/* Socket schließen */
void close_socket( socket_t *sock ){
	close(*sock);
}

int main (int argc, char **argv) {
	socket_t sock;
	char *buffer = (char *)malloc (BUF);

	if( argc < 2 ){
		printf("Usage: %s ServerA dresseServeradresse\n", *argv);
		exit(EXIT_FAILURE);
	}

	sock = create_socket(AF_INET, SOCK_STREAM, 0);
	connect_socket(&sock, argv[1], 15000);

	do {
		buffer[0] = '\0';
		printf ("Nachricht zum Versenden: ");
		fgets (buffer, BUF, stdin);
		TCP_send (&sock, buffer, strlen (buffer));
	} while (strcmp (buffer, "quit\n") != 0);
	close_socket (&sock);
	return EXIT_SUCCESS;
}
