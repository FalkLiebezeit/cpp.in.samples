/* filetest2.c */
#include <stdio.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0
#define BOOL int

int if_exist_file( const char *filename ) {
	FILE *f = fopen( filename, "r" );
	if( f != NULL ) {
		fclose(f);
		return TRUE; /* Datei existiert. */
	}
	else
		return FALSE; /* Datei existiert nicht. */
}

int main(void) {
	BOOL ex = if_exist_file( "testfile" );
	if( ex )
		printf("'testfile' existiert\n");
	else
		perror("'testfile'");
	return EXIT_SUCCESS;
}
