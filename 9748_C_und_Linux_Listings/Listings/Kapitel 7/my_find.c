/* my_find.c */
#include <stdlib.h>
#include <stdio.h>

int main (void) {
	printf("Vor dem system()-Aufruf\n");
	system("find /usr/include -name 'std*'");
	printf("Nach dem system()-Aufruf\n");
	return  EXIT_SUCCESS;
}
