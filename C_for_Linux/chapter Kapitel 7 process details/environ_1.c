/* environ_1.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>

/* Wird in keiner (modernen) Headerdatei portabel */
/* definiert, daher manuelle Einbindung.          */
extern char **environ;

int main(void) {
	int i=0;
	while(environ[i]!= NULL) {
		printf("%s\n", environ[i++]);
	}
	return EXIT_SUCCESS;
}

