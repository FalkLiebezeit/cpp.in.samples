/* Adressen.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

static void ip_adressen (const char *ip_addr) {
	struct in_addr ip;
	char *ip_str;

	if (inet_aton (ip_addr, &ip) == 0)
		return;
	printf ("\n  *** Gesamtteil der IP-Adresse *** \n");
	printf ("IP-Adresse (argv[1])                : %s\n",
		ip_addr);
	printf ("IP-Adresse als 32-Bit Wert - inet_aton() : %d\n",
		ip.s_addr);
	ip_str = inet_ntoa (ip);
	if (ip_str == NULL)
		return;
	printf ("IP-Adresse String mit inet_ntoa()     : %s\n",
		ip_str);
}

static void ip_netzwerk (const char *ip_addr) {
	struct in_addr ip, net_ip;
	unsigned long int net, net_num;

	if (inet_aton (ip_addr, &ip) == 0)
		return;
	net = inet_netof (ip);
	if (net <= 0)
		return;
	/* Netzwerkteil */
	printf ("\n  *** Netzwerkteil der IP-Adresse *** \n");
	printf ("Netzwerknummer der IP-Adresse mit "
		"inet_netof()  : %lu\n", net);
	net_ip.s_addr = net_num = ntohl (inet_netof (ip) << 8);
	printf ("--->%s", inet_ntoa (net_ip));
	printf ("--> (als 32-Bit-Wert) : %ld\n", net_num);
	net_ip = inet_makeaddr (htonl (net_num), 0);
	printf ("inet_makeaddr()->(als 32-Bit-Wert) : %d\n",
		net_ip.s_addr);
}

static void ip_lokal (const char *ip_addr) {
	struct in_addr ip, lokal_ip;
	unsigned long int lokal_num;

	if (inet_aton (ip_addr, &ip) == 0)
		return;
	printf ("\n  *** Lokaler Teil der IP-Adresse *** \n");
	lokal_ip.s_addr = lokal_num = ntohl (inet_lnaof (ip));
	printf ("--->%s", inet_ntoa (lokal_ip));
	printf ("--> (als 32-Bit-Wert) : %ld\n", lokal_num);
	lokal_ip = inet_makeaddr (0, htonl (lokal_num));
	printf ("inet_makeaddr()->(als 32-Bit-Wert) : %d\n",
		lokal_ip.s_addr);
}

static void ip_zusammen (const char *ip_addr) {
	struct in_addr ip, lokal_ip, net_ip, zusammen_ip;
	unsigned long int lokal_num, net_num;

	if (inet_aton (ip_addr, &ip) == 0)
		return;
	printf ("\n  *** Lokale Teile und Netzwerkteil "
		"zusammensetzen *** \n");
	lokal_ip.s_addr = lokal_num = ntohl (inet_lnaof (ip));
	printf ("Lokaler Teil: ");
	printf ("%20s = ", inet_ntoa (lokal_ip));
	printf ("(als 32-Bit-Wert) : %ld\n", lokal_num);
	printf ("Netzwerkteil: ");
	net_ip.s_addr = net_num = ntohl (inet_netof (ip) << 8);
	printf ("%20s = ", inet_ntoa (net_ip));
	printf ("(als 32-Bit-Wert) : %ld\n", net_num);
	zusammen_ip=inet_makeaddr( htonl (net_num),
		htonl (lokal_num));
	printf("Alles wieder mit inet_makeaddr zusammengefügt: ");
	printf ("\n%s = %d\n", inet_ntoa (zusammen_ip),
		zusammen_ip.s_addr);
}

int main (int argc, char **argv) {
	char *ptr;
	if (argc != 2)
		printf ("Verwendung %s IP-Adresse\n", *argv);
	else {
		ptr = argv[1];
		ip_adressen (ptr);
		ip_netzwerk (ptr);
		ip_lokal (ptr);
		ip_zusammen (ptr);
	}
	return EXIT_SUCCESS;
}
