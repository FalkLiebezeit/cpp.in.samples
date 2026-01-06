/* multicast-client.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* Adresse für multicast Multicast IP */
static char *host_name = "224.0.0.1";
static int port = 1234;
static struct ip_mreq command;

static int setup_multicast_socket (void) {
	int loop = 1;
	int socket_descriptor;
	struct sockaddr_in sin;

	memset (&sin, 0, sizeof (sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl (INADDR_ANY);
	sin.sin_port = htons (port);
	if ( ( socket_descriptor = socket(PF_INET,
		SOCK_DGRAM, 0)) == -1) {
		perror ("socket()");
		exit (EXIT_FAILURE);
	}
	/* Mehr mehr Prozessen erlauben, denselben Port zu nutzen */
	loop = 1;
	if (setsockopt ( socket_descriptor,
		SOL_SOCKET,
		SO_REUSEADDR,
		&loop, sizeof (loop)) < 0) {
		perror ("setsockopt:SO_REUSEADDR");
		exit (EXIT_FAILURE);
	}
	if(bind( socket_descriptor,
		(struct sockaddr *)&sin,
		sizeof(sin)) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	/* Broadcast auf dieser Maschine zulassen */
	loop = 1;
	if (setsockopt ( socket_descriptor,
		IPPROTO_IP,
		IP_MULTICAST_LOOP,
		&loop, sizeof (loop)) < 0) {
		perror ("setsockopt:IP_MULTICAST_LOOP");
		exit (EXIT_FAILURE);
	}
	/* DerJoin the broadcast group beitreten:  */
	command.imr_multiaddr.s_addr = inet_addr ("224.0.0.1");
	command.imr_interface.s_addr = htonl (INADDR_ANY);
	if (command.imr_multiaddr.s_addr == -1) {
		perror ("224.0.0.1 ist keine Multicast-Adresse\n");
		exit (EXIT_FAILURE);
	}
	if (setsockopt ( socket_descriptor,
		IPPROTO_IP,
		IP_ADD_MEMBERSHIP,
		&command, sizeof (command)) < 0) {
		perror ("setsockopt:IP_ADD_MEMBERSHIP");
	}
	return socket_descriptor;
}

int main (void) {
	int iter = 0;
	int sin_len;
	char message[256];
	int socket;
	struct sockaddr_in sin;
	struct hostent *server_host_name;

	if ((server_host_name = gethostbyname (host_name)) == 0) {
		perror ("gethostbyname");
		exit (EXIT_FAILURE);
	}
	socket = setup_multicast_socket ();
	/* Broadcast-Nachrichten empfangen */
	while (iter++ < 10) {
		sin_len = sizeof (sin);
		if (recvfrom( socket, message, 256, 0,
		(struct sockaddr *) &sin, &sin_len)==-1) {
			perror ("recvfrom");
		}
		printf ("Antwort #%-2d vom Server: %s\n",
			iter, message);
		sleep (2);
	}
	/* Multicast-Socket aus der Gruppe entfernen */
	if (setsockopt ( socket,
		IPPROTO_IP,
		IP_DROP_MEMBERSHIP,
		&command, sizeof (command)) < 0 ) {
		perror ("setsockopt:IP_DROP_MEMBERSHIP");
	}
	close (socket);
	return EXIT_SUCCESS;
}
