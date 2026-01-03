/* Zombie.c */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) {
	pid_t pid;
	switch (pid = fork ()) {
	case -1:
		printf ("Fehler bei fork()\n");
		break;
	case 0:
		printf("--- Im Kindprozess (%d) ---\n",getpid());
		printf("Elternprozess : %d\n", getppid());
		printf("--- Kindprozess beendet sich ---\n");
		exit(0);
	default:
		printf("--- Im Elternprozess (%d) ---\n",getpid());
		printf("--- Beenden mit <STRG>+<C> ---\n");
		while(1); /* Endlosschleife */
	}
	return EXIT_SUCCESS;
}
