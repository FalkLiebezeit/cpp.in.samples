/* cpy_file_mmap.c */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h.>
#include <stdlib.h>
#include <string.h>

static void write3 (int fd_quelle, int fd_ziel) {
	struct stat statptr;
	char *quelle, *ziel;

	/* Größe der Quelldatei ermitteln */
	if (fstat (fd_quelle, &statptr) < 0) {
		perror ("stat");
		exit (EXIT_FAILURE);
	}
	/* Dateigröße für Ziel */
	if (lseek (fd_ziel, statptr.st_size - 1, SEEK_SET) == -1) {
		perror ("lseek");
		exit (EXIT_FAILURE);
	}
	/* Am Ende der neuen Datei(größe) ein Byte schreiben */
	write (fd_ziel, " ", 1);
	/* mapped-Bereich für Quelldatei einrichten  */
	if ((quelle =mmap (0, statptr.st_size, PROT_READ, MAP_SHARED,fd_quelle, 0)) == -1) {
		perror ("mmap");
		exit (EXIT_FAILURE);
	}
	/* mapped-Bereich für Zieldatei einrichten */
	if ((ziel =mmap (0, statptr.st_size, PROT_READ | PROT_WRITE,MAP_SHARED, fd_ziel, 0)) == -1) {
		perror ("mmap");
		exit (EXIT_FAILURE);
	}
	/* Daten vom Hauptspeicherbereich quelle in den */
	/* Hauptspeicherbereich ziel kopien */
	memcpy (ziel, quelle, statptr.st_size);

	/* Denn neu kopierten mapped-Bereich auch für   */
	/* die Datei aktuallisieren */
	if ((msync (ziel, statptr.st_size, MS_ASYNC)) == -1) {
		perror ("msync");
		exit (EXIT_FAILURE);
	}
	/* mapped-Bereich wieder freigeben */
	munmap (quelle, statptr.st_size);
	munmap (ziel, statptr.st_size);
}

int main (int argc, char **argv) {
	int fd_r, fd_w; /* Filedeskriptoren */
	/* Zugriffsrechte für die neue Datei: -rw-rw-r-- */
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	char *read_file, *write_file;

	/* Alle Zugriffsrechte der Dateikreierungsmaske erlauben */
	umask (0);

	if (argc < 3) {
		fprintf (stderr, "Usage: %s quelle ziel\n", argv[0]);
		return EXIT_FAILURE;
	}
	read_file = argv[1];
	write_file = argv[2];

	fd_r = open (read_file, O_RDONLY);
	fd_w = open (write_file, O_RDWR | O_EXCL | O_CREAT, mode);

	if ((fd_r == -1) || (fd_w == -1)) {
		perror ("Fehler bei open : ");
		return EXIT_FAILURE;
	}
	write3 (fd_r, fd_w);
	close(fd_r);
	close(fd_w);
	return EXIT_SUCCESS;
}
