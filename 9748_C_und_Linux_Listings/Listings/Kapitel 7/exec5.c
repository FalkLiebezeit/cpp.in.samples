/* exec5.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {
	return execlp("/bin/ls","ls","-l",getenv("HOME"),NULL);
}

