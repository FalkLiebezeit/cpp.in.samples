/* syslog-demo.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char **argv) {
	openlog( "logging",
		LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL0 );
	/*  Etwas ist passiert -> schick es an /dev/tty1. */
	syslog(LOG_NOTICE, "Hallo Welt mit syslog\n");
	/* Ende */
	closelog();
	return EXIT_SUCCESS;
}
