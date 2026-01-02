/* fifo1.c */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#define FIFO "fifo0001"

int main (void) {
	struct stat attribut;
	/* Wir erzeugen eine FIFO-Warteschlange. */
	if ((mkfifo (FIFO,  S_IRUSR | S_IWUSR)) == -1) {
		/* FIFO bereits vorhanden – dies ist kein fataler Fehler. */
		if(errno == EEXIST)
			perror ("mkfifo()");
		else {
			perror("mkfifio()");
			exit (EXIT_FAILURE);
		}
	}
	if (stat (FIFO, &attribut) == -1) {
		perror ("stat()");
		exit (EXIT_FAILURE);
	}
	printf("Dateiart von %s ermitteln ...\n",FIFO);
	if (S_ISREG (attribut.st_mode))
		printf ("Reguläre Datei\n");
	else if (S_ISDIR (attribut.st_mode))
		printf ("Verzeichnis\n");
	#ifdef S_ISSOCK
	else if (S_ISSOCK (attribut.st_mode))
		printf ("Socket\n");
	#endif
	else if (S_ISFIFO (attribut.st_mode))
		printf ("FIFO\n");
	else
		printf ("Unbekannte Dateiart\n");
	return EXIT_SUCCESS;
}
