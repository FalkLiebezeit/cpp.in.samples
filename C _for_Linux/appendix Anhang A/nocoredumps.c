/* nocoredumps.c */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <errno.h>

#ifndef DEBUG
void no_core(void) {
	struct rlimit rlim;
	int ret;
	rlim.rlim_cur = rlim.rlim_max = 0;
	ret = setrlimit(RLIMIT_CORE, &rlim);
	if(ret == -1)
		perror("Fehler bei setrlimit");
	else
		printf("Kein Core Dump wird ggf. erzeugt...\n");
}
#endif

int main(int argc, char **argv) {
	/* .... */
	#ifndef DEBUG
		no_core();
	#endif
	return EXIT_SUCCESS;
}
