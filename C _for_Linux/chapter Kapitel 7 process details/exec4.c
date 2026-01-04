/* exec4.c */
#include <stdio.h>
#include <unistd.h>

int main (void) {
	char *environment[4];

	environment[0] = "SHELL=/bin/csh";
	environment[1] = "LOGNAME=heino";
	environment[2] = "OSTYPE=LiNuX";
	environment[3] = NULL;

	return execle( "/usr/bin/printenv", "printenv",
		NULL, environment );
}

