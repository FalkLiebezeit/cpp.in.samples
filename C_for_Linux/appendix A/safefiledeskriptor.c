/* safefiledeskriptor.c */
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <errno.h>
/* enhält den Pfad zu /dev/null - _PATH_DEVNULL*/
#include <paths.h>

/* Falls getdtablesize fehlschlägt auf 256 setzen */
#ifndef OPEN_MAX
#define OPEN_MAX 256
#endif

/* Standard-Filedeskriptoren ggf. mit /dev/null öffnen */
static int fd_devnull(int fd) {
	FILE *fz = NULL;

	switch(fd) {
		case 0 :  /* Standardeingabe - stdin */
			fz = freopen(_PATH_DEVNULL, "rb", stdin),
		break;
		case 1 :  /* Standardausgabe - stdout */
			fz = freopen(_PATH_DEVNULL, "wb", stdout);
		break;
		case 2 :  /* Standardfehlerausgabe - stderr */
			fz = freopen(_PATH_DEVNULL, "wb", stderr);
		break;
		default:
		break;
	}
	return (fz && fileno(fz) == fd);
}

/* Diese Funktion behandelt die Filedeskriptoren */
void safe_descriptor(void) {
	int fd, fdsize;
	struct stat st;

	/* Wieviele Dateien dürften insges. geöffnet sein ... */
	if ((fdsize = getdtablesize( )) == -1)
		fdsize = OPEN_MAX;
	/* Alle Filedeskriptoren bis auf die Standard-Deskriptoren schließen */
	for (fd = 3;  fd < fdsize;  fd++)
		close(fd);

	/* Jetzt die Standard-Filedeskriptoren behandeln - mit fstat()
	 * überprüfen, ob vorhanden und ungleich EBADF oder Standard-
	 * Deskriptor mit /dev/null öffnen. Schlägt alles fehl,
	 * Programm mit abort() beenden, da Fehlerausgabe sinnlos wäre.
	 */
	for (fd = 0;  fd < 3;  fd++)
		if (fstat(fd, &st) == -1 && (errno != EBADF ||!fd_devnull(fd)))
			abort();
}

int main(int argc, char **argv) {
	safe_descriptor();
	return EXIT_SUCCESS;
}
