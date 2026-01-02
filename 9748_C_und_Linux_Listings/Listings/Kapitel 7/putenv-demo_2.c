/* putenv-demo_2.c */
#include <stdio.h>
#include <stdlib.h>

int main (void) {
	char buf[] = "key=value";
	putenv(buf);
	printf("buf=%p, getenv=%p (%s)\n",
		buf, getenv("key"), getenv("key"));
	printf("heap  test: %p\n", malloc(1));
	printf("stack test: %p\n", &buf);
	return EXIT_SUCCESS;
}

