/* filetest.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0
#define BOOL int

int if_exist_file( const char *filename ) {
	FILE *f = fopen( filename, "r" );
	if( errno != ENOENT ) {
		fclose(f);
		return TRUE; /* Datei existiert. */
	}
	else
		return FALSE; /* Datei existiert nicht. */
	}
}

int main(void) {
	BOOL ex = if_exist_file( "testfile" );
	if (ex)
		printf("'testfile' existiert\n");
	else
		printf("'testfile' existiert nicht\n");
	return EXIT_SUCCESS;
}
