/* prio_child.c */
#include <stdlib.h>
#include <unistd.h.>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

/* Bitte anpassen. */
#define PROGRAM "/usr/bin/find"
/* Bitte anpassen. */
#define PRIORITY 19
/* max. Argumente aus der Kommandozeile */
#define MAX_ARGS 1024

int main (int argc, char **argv) {
	int i;
	pid_t pid;
	char *args[MAX_ARGS + 1] = { PROGRAM, NULL };
	seteuid (getuid ());  /* Privilegien entfernen */
	/* Argumente kopieren */
	for (i = 1; i < argc && i < MAX_ARGS; i++)
		args[i] = argv[i];
	args[i] = NULL;
	/* neuen Prozess für PROGRAMM erzeugen */
	pid = fork ();
	if (pid == 0) {
		/* neuen Prozess PROGRAMM starten */
		execvp (PROGRAM, args);
	}
	else {
		/* Privilegien wieder einführen */
		seteuid (0);
		/* Priorität für PROGRAMM (pid) auf PRIORITY setzen */
		setpriority (PRIO_PROCESS, pid, PRIORITY);
	}
	return EXIT_SUCCESS;
}
