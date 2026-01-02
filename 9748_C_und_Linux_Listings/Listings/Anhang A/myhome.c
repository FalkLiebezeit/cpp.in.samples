/* myhome.c */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h.>
#include <stdlib.h>
#include <pwd.h.>

int main(int argc, char **argv) {
	uid_t uid;
	struct passwd *pwd;

	uid = getuid( );
	printf("UID des Users ist:  %d.\n", (int)uid);
	if (!(pwd = getpwuid(uid))) {
		printf("Kann nicht aus der Passwort-Datei lesen ...\n");
		endpwent( );
		exit(EXIT_FAILURE);
	}
	printf("Heimverzeichnis nach Passwort-Datei ist: %s\n",pwd->pw_dir);
	printf("Heimverzeichnis nach getenv(\"HOME\") ist: %s\n",getenv("HOME"));

	if(strcmp( pwd->pw_dir, getenv("HOME")) != 0 ) {
		printf("Umgebungsvariablen \"HOME\" wurde manipuliert\n");
		exit(EXIT_FAILURE);
	}
	endpwent();
	return EXIT_SUCCESS;
}
