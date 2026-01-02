/* sende.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <termios.h>

int main(int argc, char **argv) {
	printf("Nachricht von Terminal %s\n%s",
		ttyname(STDIN_FILENO), *++argv);
	return EXIT_SUCCESS;
}

