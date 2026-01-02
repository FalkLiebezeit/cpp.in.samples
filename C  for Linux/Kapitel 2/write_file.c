/* write_file.c */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h.>

int main(int argc, char **argv) {
	/* Zugriffsrechte für die neue Datei: -rw-rw-r-- */
	mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
	ssize_t size;
	int fd; /* Filedeskriptor */
	char *str;
	/* alle Zugriffsrechte der Einschränkungsmaske erlauben */
	umask(0);
	/* zweites Argument der Kommandozeile auswerten */
	if(argc < 2) {
		fprintf(stderr, "Usage: %s datei_zum_oeffnen\n",
		*argv);
		return EXIT_FAILURE;
	}
	if(argc < 3) { str = "Keine Angaben gemacht\n"; }
	else { str = argv[2]; }
	size = strlen(str);
	/*----------------------------------------------
	neue Datei erzeugen               (O_CREAT)
	zum Schreiben                     (O_WRONLY)
	Daten am Ende hinzufügen          (O_APPEND)
	Zugriffsrechte der Datei erteilen (modus)
	----------------------------------------------*/
	fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, mode);
	if(fd == -1) {
		perror("Fehler bei open()");
		return EXIT_FAILURE;
	}
	if(write(fd, str, size) != size)
		perror("Fehler bei write()");
	return EXIT_SUCCESS;
}
