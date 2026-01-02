/* servent.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int main (int argc, char **argv) {
	struct servent *service_info;
	char **ptr;

	if( argc != 3) {
		printf("Usage: %s dienst protokoll\n", *argv);
		return EXIT_FAILURE;
	}
	service_info = getservbyname( argv[1], argv[2] );
	if( service_info == NULL ) {
		herror("Konnte den Service nicht finden\n");
		return EXIT_FAILURE;
	}
	printf("Service   : %s\n", service_info->s_name);
	printf("Port      : %d\n", ntohs( service_info->s_port) );
	printf("Aliasse       : \n");
	ptr = service_info->s_aliases;
	while(*ptr != NULL) {
		printf("%s\n", *ptr++);
	}
	printf("Protokoll : %s\n", service_info->s_proto);
	return EXIT_SUCCESS;
}
