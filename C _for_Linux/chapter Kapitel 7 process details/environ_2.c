/* environ_2.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>

int main(int argc, char **argv, char **envp) {
	while(*envp != NULL) {
		printf("%s\n", *envp++);
	}
	return EXIT_SUCCESS;
}
