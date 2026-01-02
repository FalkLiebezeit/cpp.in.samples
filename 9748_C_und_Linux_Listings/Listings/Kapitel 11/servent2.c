/* servent2.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main (int argc, char **argv) {
	struct servent *service_info;
	int port = 0;
	while (port++ < 100) {
		service_info = getservbyport (htons (port), "tcp");
		if (service_info == NULL)
			printf ("Port %d : Keine Infos\n", port);
		else {
			printf ("Service : %10s ", service_info->s_name);
			printf ("Port    : %3d ",
				ntohs (service_info->s_port));
			printf ("Protokoll : %5s\n", service_info->s_proto);
		}
	}
	return EXIT_SUCCESS;
}
