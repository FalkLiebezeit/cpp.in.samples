/* key_ftok.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(void) {
	key_t key1, key2;
	key1 = ftok(".", 'a');
	key2 = ftok("/usr/include", 'x');
	printf("key1: %d key2: %d\n",key1, key2);
	return EXIT_SUCCESS;
}
