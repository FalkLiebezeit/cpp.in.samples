/* my_tty.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <termios.h>
static char termname[L_ctermid];

int main (void) {
	const char *ptr = ctermid (termname);
	if (ptr != NULL)
		printf ("Kontrollterminalname = %s\n", ptr);
	else
		printf("Konnte Terminalname nicht ermitteln\n");
	return EXIT_SUCCESS;
}
