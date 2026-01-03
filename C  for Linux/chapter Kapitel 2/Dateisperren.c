/* Dateisperren.c */
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h.>
#define FNAME "locki.lck"

void status(struct flock *lock) {
	printf("Status: ");
	switch(lock->l_type) {
		case F_UNLCK:
			printf("F_UNLCK (Sperre aufgehoben)\n");
		break;
		case F_RDLCK:
			printf("F_RDLCK (PID: %d) (Lesesperre)\n",
				lock->l_pid);
		break;
		case F_WRLCK:
			printf("F_WRLCK (PID: %d) (Schreibsperre)\n",
				lock->l_pid);
		break;
	}
}

void unlock(int fd, struct flock *lock) {
	memset(lock, 0, sizeof(struct flock));
	lock->l_type = F_UNLCK; /* Sperre aufheben */
	if(fcntl(fd, F_SETLK, lock) < 0)
		perror("Fehler: fcntl(fd, F_SETLK, F_UNLCK)");
	else
		status(lock);
}

void locki(int fd, struct flock *lock) {
	memset(lock, 0, sizeof(struct flock));
	lock->l_type   = F_WRLCK;  // Schreibsperre
	lock->l_start  = 0;        // kein Offset
	lock->l_whence = SEEK_SET; // vom Anfang der Datei
	lock->l_len    = 0;        // bis zum Ende der Datei
	lock->l_pid    = getpid(); // Prozessnummer der Sperre
	if(fcntl(fd, F_SETLK, lock) < 0)
		perror("Fehler: fcntl(fd, F_SETLK, F_WRLCK)");
	else
		status(lock);
}


int main(int argc, char **argv) {
	struct flock lock;
	char puffer[100];
	int fd, n;

	fd=open(FNAME, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	memset(&lock, 0, sizeof(struct flock));
	fcntl(fd, F_GETLK, &lock);
	status(&lock);
	printf("\nEingabe machen: ");
	fflush(stdout);
	while((n = read(STDIN_FILENO, puffer, 100)) > 1) {
		locki(fd, &lock);
		write(fd, puffer, n);
		unlock(fd, &lock);
	}
	close(fd);
	return EXIT_SUCCESS;
}
