/* prozessdaten.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <sys/types.h>

int main( void ) {
	printf("Ich bin Nummer %d\n", getpid());
	printf("Mein Elternprozess hat die Nummer %d\n",
		getppid());
	printf("Die User-ID effektiv : %d --> real: %d\n",
		geteuid(),getuid());
	printf("Die Group-ID effektiv: %d --> real: %d\n",
		getegid(),getgid());
	return EXIT_SUCCESS;
}
