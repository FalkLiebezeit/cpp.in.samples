/* my_getpid.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main (void) {
	char buf[64];
	int pid;

	memset(buf, '\0', sizeof(buf));
	readlink("/proc/self", buf, sizeof(buf) - 1);
	sscanf(buf, "%d", &pid);
	printf("Meine Prozess-ID lautet: %d\n", pid);
	return EXIT_SUCCESS;
}
