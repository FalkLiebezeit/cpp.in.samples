/* multi_server.c */
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

/* Erzeugt die Bindung an die Serveradresse
* (genauer an einen bestimmten Port). */
void bind_socket(socket_t *sock, unsigned long add ress,
	unsigned short port) {
	struct sockaddr_in server;

	memset( &server, 0, sizeof (server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(add ress);
	server.sin_port = htons(port);
	if (bind( *sock, (struct sockaddr*)&server,
		sizeof(server)) < 0 )
	error_exit("Kann das Socket nicht \"binden\"");
}

/* Teile dem Socket mit, dass Verbindungsw¸nsche
* von Clients entgegengenommen werden. */
void listen_socket( socket_t *sock ) {
	if(listen(*sock, 5) == -1 )
		error_exit("Fehler bei listen");
}

/* Bearbeite die Verbindungsw¸nsche von Clients.
* Der Aufruf von accept() blockiert so lange,
* bis ein Client Verbindung aufnimmt. */
void accept_socket(socket_t *socket, socket_t *new_socket){
	struct sockaddr_in client;
	int len;

	len = sizeof(client);
	*new_socket = accept( *socket,(struct sockaddr *)&client,
		&len );
	if (*new_socket  == -1)
		error_exit("Fehler bei accept");
}

/* Daten empfangen via TCP */
void TCP_recv( socket_t *sock, char *data, size_t size) {
	int len;
	len = recv (*sock, data, size, 0);
	if( len > 0 || len != -1 )
		data[len] = '\0';
	else
		error_exit("Fehler bei recv()");
}

/* Socket schlieﬂen */
void close_socket( socket_t *sock ){
	close(*sock);
}

int main (void) {
	socket_t sock1, sock2, sock3;
	int i, ready, sock_max, max=-1;
	int client_sock[FD_SETSIZE];
	fd_set gesamt_sock, lese_sock;
	char *buffer = (char*) malloc (BUF);

	sock_max = sock1 = create_socket(AF_INET, SOCK_STREAM, 0);

	bind_socket( &sock1, INADDR_ANY, 15000 );
	listen_socket (&sock1);

	for( i=0; i<FD_SETSIZE; i++)
		client_sock[i] = -1;
	FD_ZERO(&gesamt_sock);
	FD_SET(sock1, &gesamt_sock);

	for (;;) {
		/* Immer immer aktualisieren */
		lese_sock = gesamt_sock;
		/* Hier wird auf die Ankunft von Daten oder
		* neuer neuen Verbindungen von Clients gewartet. */
		ready=select(sock_max+1, &lese_sock, NULL, NULL, NULL);
		/* Eine neue Clientverbindung ... ? */
		if( FD_ISSET(sock1, &lese_sock)) {
			accept_socket( &sock1, &sock2 );
			/* Freien freien Platz f¸r (Socket-)Deskriptor
			* in client_sock suchen und vergeben */
			for( i=0; i< FD_SETSIZE; i++)
				if(client_sock[i] < 0) {
					client_sock[i] = sock2;
					break;
				}
				/* Mehr als FD_SETSIZE Clients sind nicht mˆglich. */
				if( i == FD_SETSIZE )
					error_exit("Server ¸berlastet - zu viele Clients");
				/* Den den neuen (Socket-)Deskriptor zur
				* (Gesamt-)Menge hinzuf¸gen */
				FD_SET(sock2, &gesamt_sock);
				/* select() benˆtigt die hˆchste
				* (Socket-)Deskriptor-Nummer. */
				if( sock2 > sock_max )
					sock_max = sock2;
				/* hˆchster Index f¸r client_sock
				* f¸r die anschlieﬂende Schleife benˆtigt */
				if( i > max )
					max = i;
				/* ... weitere (Lese-)Deskriptoren bereit? */
				if( --ready <= 0 )
					continue; // Nein ...
			} //if(FD_ISSET ...

			/* Ab hier werden alle Verbindungen von Clients auf
			* die Ankunft von neuen Daten ¸berpr¸ft. */
			for(i=0; i<=max; i++) {
				if((sock3 = client_sock[i]) < 0)
					continue;
			/* (Socket-)Deskriptor gesetzt ... */
			if(FD_ISSET(sock3, &lese_sock)){
				/* ... dann die Daten lesen */
				TCP_recv (&sock3, buffer, BUF-1);
				printf ("Nachricht empfangen: %s\n", buffer);
				/* Wenn quit erhalten wurde ... */
				if (strcmp (buffer, "quit\n") == 0) {
					/* ... hat sich der Client beendet. */
					// Socket schlieﬂen
					close_socket (&sock3);
					// aus Menge lˆschen
					FD_CLR(sock3, &gesamt_sock);
					client_sock[i] = -1;        // auf -1 setzen
					printf("Ein Client hat sich beendet\n");
				}
				/* Noch lesbare Deskriptoren vorhanden ... ? */
				if( --ready <= 0 )
					break; // Nein ...
			}
		}
	} // for(;;)
	return EXIT_SUCCESS;
}
