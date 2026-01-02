/* passwortinfo2.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h.>
#include <string.h>

struct passwd *getpasswd(const char *loginname) {
	struct passwd *pas_ptr;
	while( pas_ptr=getpwent() ) {
		if( strcmp(pas_ptr->pw_name, loginname) == 0) {
			endpwent();
			return pas_ptr;
		}
	}
	endpwent();
	return NULL;
}

int main(int argc, char *argv[]) {
	struct passwd *pas_ptr;
	if( argc != 2 ) {
	fprintf(stderr, "Usage: %s Name\n", argv[0]);
	exit (EXIT_FAILURE);
	}
	pas_ptr=getpasswd(argv[1]);
	if(pas_ptr == NULL) {
		printf("Konnte nichts über %s ermitteln\n", argv[1]);
		exit (EXIT_FAILURE);
	}
	printf("Folgendes wurde zu %s ermittelt: \n", argv[1]);
	printf("Benutzername     : %s\n", pas_ptr->pw_name);
	printf("Benutzernummer   : %d\n", pas_ptr->pw_uid);
	printf("Gruppennummer    : %d\n", pas_ptr->pw_gid);
	printf("Kommentar        : %s\n", pas_ptr->pw_gecos);
	printf("Login-Verzeichnis: %s\n", pas_ptr->pw_dir);
	printf("Login-Shell      : %s\n", pas_ptr->pw_shell);
	return EXIT_SUCCESS;
}
