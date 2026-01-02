/* exec6.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {
	char *argumente[4];
	argumente[0] = "ls";
	argumente[1] = "-l";
	argumente[2] = getenv("HOME");
	argumente[3] = NULL;
	return execvp ("/bin/ls", argumente);
}
