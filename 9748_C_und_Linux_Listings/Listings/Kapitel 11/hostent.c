/* hostent.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char **argv) {
	struct hostent *host;
	struct in_addr ip, **ip_ptr;
	char **ptr;

	if( argc != 2 )
	printf("Usage: %s (Rechnername oder IP-Adresse)\n",
		*argv);
	else {
		/* Argument als IP-Adresse ...? */
		if( inet_aton( argv[1], &ip ) != 0 )
			host=gethostbyaddr( (const void *)&ip,
				sizeof(ip),AF_INET );
		/* Argument als Rechnername */
		else
			host = gethostbyname( argv[1] );
		if( host == NULL ) {
			herror("Konnte Rechner nicht finden");
			return EXIT_FAILURE;
		}
		printf("Hostname    : %s\n", host->h_name);
		printf("Aliasse        :\n");
		ptr=host->h_aliases;
		while( *ptr != NULL ) {
			printf("\t%s\n", *ptr++);
		}
		printf("IP-Adressen :\n");
		ip_ptr = (struct in_addr **)host->h_addr_list;
		while(*ip_ptr != NULL) {
			printf("\t%s\n", inet_ntoa( **ip_ptr++));
		}
	}
	return EXIT_SUCCESS;
}
