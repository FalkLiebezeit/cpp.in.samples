/* eventloop_2.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h.>
#include <sched.h.>
#ifndef _POSIX_PRIORITY_SCHEDULING
	#error "sched_yield() ist hier nicht vorhanden"
#endif

static int event_loop(void) { // Die Warteschleifen-Funktion muss static sein.
	int ereignis = 0;
	/* eine Ereignisschleife */
	if( ereignis )
		return 1;
	else
		return 0;
}

int main() {
	int loop = 0;
	while( !loop ) {
	loop = event_loop();
	sched_yield();
	}
	return EXIT_SUCCESS;
}
