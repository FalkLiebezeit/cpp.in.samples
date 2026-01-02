/* dup-Beispiel.c */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h.>

static void test_write(const char *str) {
	write(STDOUT_FILENO, str, strlen(str));
	return;
}

int main(int argc, char **argv) {
	mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
	int fd1, fd2, fd3;

	// alle Zugriffsrechte der Einschränkungsmaske erlauben
	umask(0);
	fd1 = open("file1", O_WRONLY | O_CREAT, mode);
	fd2 = open("file2", O_WRONLY | O_CREAT, mode);
	if(fd1 == -1 || fd2 == -1) {
		perror("Fehler bei open()");
		return EXIT_FAILURE;
	}

	test_write("Zeile 1\n");
	dup2(fd1, STDOUT_FILENO);
	test_write("Zeile 2\n");
	dup2(fd2, STDOUT_FILENO);
	test_write("Zeile 3\n");
	test_write("Zeile 4\n");
	dup2(fd1, STDOUT_FILENO);
	test_write("Zeile 5\n");
	dup2(fd2, STDOUT_FILENO);
	test_write("Zeile 6\n");
	test_write("Zeile 7\n");
	close(fd1);
	close(fd2);

	fd3 = dup(STDERR_FILENO);
	write(fd3, "Schwerer Fehler ...\n",
		strlen("Schwerer Fehler ...\n"));
	return EXIT_SUCCESS;
}
