/* my_limit.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

void limits( int resource ) {
	struct rlimit l;

	if( getrlimit( resource, &l ) < 0 ) {
		printf("keine Angaben\n");
		return;
	}
	printf("Soft Limit: ");
	(l.rlim_cur == RLIM_INFINITY)?
	printf("kein Limit  "):
	printf("%ld  ",l.rlim_cur);
	printf("Hard Limit: ");
	(l.rlim_max == RLIM_INFINITY)?
	printf("kein Limit\n"):
	printf("%ld  \n",l.rlim_max);
}

int main( void ) {
	unsigned int i;
	const int limit[] = {
		RLIMIT_CPU, RLIMIT_CORE, RLIMIT_DATA, RLIMIT_FSIZE,
		/* RLIMIT_LOCKS,*/ RLIMIT_MEMLOCK,
		RLIMIT_NOFILE, /* bei BSD RLIMIT_OFILE */
		RLIMIT_NPROC, RLIMIT_RSS, RLIMIT_STACK,
	};
	const char *s_limit[] = {
		"RLIMIT_CPU", "RLIMIT_CORE", "RLIMIT_DATA",
		"RLIMIT_FSIZE", /* "RLIMIT_LOCKS",*/ "RLIMIT_MEMLOCK",
		"RLIMIT_NOFILE", /* bei BSD RLIMIT_OFILE */
		"RLIMIT_NPROC", "RLIMIT_RSS", "RLIMIT_STACK",
	};

	for( i = 0; i< sizeof(limit)/sizeof(long); i++) {
		printf("%s = ",s_limit[i]);
		limits( limit[i] );
	}
	return EXIT_SUCCESS;
}
