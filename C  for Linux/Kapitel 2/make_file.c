/* make_file.c */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>

int main(int argc, char **argv) {
	// Zugriffsrechte für die neue Datei: -rw-rw-r--
	mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
	const char *new_file;
	int fd; // Filedeskriptor
	// alle Zugriffsrechte der Einschränkungsmaske erlauben
	umask(0);
	// zweites Argument der Kommandozeile auswerten
	if(argv[1] == NULL) {
		fprintf(stderr, "Usage: %s datei_zum_oeffnen\n",
		*argv);
		return EXIT_FAILURE;
	}
	new_file = argv[1];
	/*--------------------------------------------------
	Neue Datei erzeugen                   (O_CREAT)
	zum Schreiben                         (O_WRONLY)
	falls Datei existiert, nicht erzeugen (O_EXCL)
	Zugriffsrechte der Datei erteilen     (modus)
	--------------------------------------------------*/
	fd = open(new_file, O_WRONLY | O_EXCL | O_CREAT, mode);
	if(fd == -1) {
		perror("Fehler bei open ");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
