/* filecopy.c */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>

#define BLOCKSIZE 64 // Bytes

// write2() aus obigem Codeblock übernehmen
static ssize_t write2(int, const void *, size_t);

int main(int argc, char **argv) {
	// Zugriffsrechte für die neue Datei: -rw-rw-r--
	mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
	char buffer[BLOCKSIZE];
	int fd_r, fd_w; // Filedeskriptoren
	int n;

	// alle Zugriffsrechte der Einschränkungsmaske erlauben
	umask(0);

	if(argc < 3) {
		fprintf(stderr, "> %s quelldatei zieldatei\n", *argv);
		return EXIT_FAILURE;
	}

	fd_r = open(argv[1], O_RDONLY);
	fd_w = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, mode);
	if(fd_r == -1 || fd_w == -1) {
		perror("Fehler bei open()");
		return EXIT_FAILURE;
	}
	while((n = read(fd_r, buffer, BLOCKSIZE)) > 0)
		if(write2(fd_w, buffer, n) < 0)
			perror("Fehler bei write()");
	return EXIT_SUCCESS;
}
