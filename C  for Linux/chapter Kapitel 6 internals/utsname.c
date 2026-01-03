/* utsname.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <string.h>

int main(int argc, char *argv[]) {
	struct utsname uts_info;

	if( uname(&uts_info) < 0 ) {
		fprintf(stderr, "Fehler bei uname()\n");
		exit (EXIT_FAILURE);
	}

	printf("Folgende Angaben wurden ermittelt: \n");
	printf("Betriebssystem   : %s\n", uts_info.sysname);
	printf("Knotenname       : %s\n", uts_info.nodename);
	printf("Release          : %s\n", uts_info.release);
	printf("Version          : %s\n", uts_info.version);
	printf("Architektur      : %s\n", uts_info.machine);
	#define __USE_GNU
	printf("Domainname       : %s\n", uts_info.__domainname);

	return EXIT_SUCCESS;
}
