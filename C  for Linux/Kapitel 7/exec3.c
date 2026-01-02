/* exec3.c */
#include <stdio.h>
#include <unistd.h>

int main (void) {
	char *argumente[4] = { "ls", "-l", "/usr/bin", NULL };
	return execv ("/bin/ls", argumente);
}

