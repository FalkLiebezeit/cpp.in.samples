/* daemon.c */
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

static sighandler_t
handle_signal (int sig_nr, sighandler_t signalhandler) {
	struct sigaction neu_sig, alt_sig;

	neu_sig.sa_handler = signalhandler;
	sigemptyset (&neu_sig.sa_mask);
	neu_sig.sa_flags = SA_RESTART;
	if (sigaction (sig_nr, &neu_sig, &alt_sig) < 0)
		return SIG_ERR;
	return alt_sig.sa_handler;
}

static void start_daemon (const char *log_name, int facility) { // Muss static sein.
	int i;
	pid_t pid;

	/* Elternprozess beenden, somit haben wir einen Waisen, */
	/* dessen sich jetzt vorerst init annimmt.              */
	if ((pid = fork ()) != 0)
		exit (EXIT_FAILURE);

	/* Kindprozess wird zum Sessionführer. Misslingt  */
	/* dies, kann der Fehler daran liegen, dass der   */
	/* Prozess bereits Sessionführer ist.             */
	if (setsid() < 0) {
		printf("%s kann nicht Sessionführer werden!\n",
			log_name);
		exit (EXIT_FAILURE);
	}
	/* Signal SIGHUP ignorieren */
	handle_signal (SIGHUP, SIG_IGN);
	/* Oder einfach: signal(SIGHUP, SIG_IGN) ... */
	/* das Kind terminieren */
	if ((pid = fork ()) != 0)
		exit (EXIT_FAILURE);

	/* Gründe für das Arbeitsverzeichnis:
	* + core-Datei wird im aktuellen Arbeitsverzeichnis
	*   hinterlegt,
	*   damit bei Beendigung mit umount das Dateisystem
	*   sicher abgehängt werden kann.
	*/
	chdir ("/");

	/* Damit wir nicht die Bitmaske des Elternprozesses   */
	/* erben bzw. diese bleibt, stellen wir sie auf 0.    */
	umask (0);

	/* Wir schließen alle geöffneten Filedeskriptoren ... */
	for (i = sysconf (_SC_OPEN_MAX); i > 0; i--)
		close (i);

	/* Da unser Dämonprozess selbst kein Terminal für  */
	/* die Ausgabe hat ... */
	openlog ( log_name,
		LOG_PID | LOG_CONS| LOG_NDELAY, facility );
}

int main (int argc, char **argv) {
	int time   = 15;

	start_daemon ("meinDaemon", LOG_LOCAL0);
	while (1) {
		/* Enlosschleifen: Hier sollte nun der Code für den
		* Dämon stehen, was immer er auch tun soll,
		* bspw. E-Mails abholen, versenden (was keine
		* Anregung sein soll,  mit dem Spammen anzufangen);
		* bei Fehlermeldungen beispielsweise:
		* if(dies_ist_passiert)
		*    syslog(LOG_WARNING, "dies_ist_passiert");
		* else if(das_ist_Passiert)
		*    syslog(LOG_INFO, "das_ist_passiert");
		*/
		syslog( LOG_NOTICE, "Dämon gestartet ...\n");
		sleep(time);
		syslog( LOG_NOTICE,
			"Dämon läuft bereits %d Sekunden\n", time );
		break;
	}
	syslog( LOG_NOTICE, "Dsvk.mon hat sich beendet\n");
	closelog();
	return EXIT_SUCCESS;
}
