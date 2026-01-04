/* threads4.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_THREADS 3
#define BUF 255

/* Funktion ermittelt die Zuteilungsstrategie *
* und Priorität eines Threads */
static void getprio( pthread_t id ) {
	int policy;
	struct sched_param param;

	printf("\t->Thread %ld: ", id);
	if((pthread_getschedparam(id, &policy, &param)) == 0  ) {
		printf("Zuteilung: ");
		switch( policy ) {
			case SCHED_OTHER : printf("SCHED_OTHER; "); break;
			case SCHED_FIFO : printf("SCHED_FIFO; "); break;
			case SCHED_RR : printf("SCHED_RR; "); break;
			default : printf("Unbekannt; "); break;
		}
		printf("Priorität: %d\n", param.sched_priority);
	}
}

/* Funktion zum Setzen der Zuteilungsstrategie *
* und Prioriät eines Threads */
static void setprio( pthread_t id, int policy, int prio ) {
	struct sched_param param;

	param.sched_priority=prio;
	if((pthread_setschedparam( pthread_self(),
		policy, &param)) != 0  ) {
		printf("Konnte Zuteilungsstrategie nicht ändern\n");
		pthread_exit((void *)pthread_self());
	}
}

static void thread_prio_demo(void *name) {
	int policy;
	struct sched_param param;
	/* Aktuelle Zuteilungsstrategie und Priorität erfragen */
	getprio(pthread_self());
	/* Ändern darf hier nur der root */
	if( getuid() != 0 ) {
		printf("Verändern geht nur mit Superuser-Rechten\n");
		pthread_exit((void *)pthread_self());
	}
	/* Neue Zuteilungsstrategie und Priorität festsetzen */
	setprio(pthread_self(), SCHED_RR, 2);
	/* Nochmals abfragen, ob erfolgreich verändert ... */
	getprio(pthread_self());
	/* Thread-Ende */
	pthread_exit((void *)pthread_self());
}

int main (void) {
	int i;
	static int ret[MAX_THREADS];
	static pthread_t th[MAX_THREADS];

	printf("->Haupt-Thread (ID:  %ld) gestartet ...\n",
		pthread_self());
	/* Threads erzeugen */
	for (i = 0; i < MAX_THREADS; i++) {
		if (pthread_create ( &th[i],NULL, &thread_prio_demo,
			NULL) != 0) {
			printf ("Konnte keinen Thread erzeugen\n");
			exit (EXIT_FAILURE);
		}
	}
	/* Auf die Threads warten */
	for (i = 0; i < MAX_THREADS; i++)
		pthread_join (th[i], &ret[i]);
	/* Rückgabe der Threads auswerten */
	for (i = 0; i < MAX_THREADS; i++)
		printf("\t<-Thread %ld mit Arbeit fertig\n", ret[i]);
	printf("->Haupt-Thread (ID:  %ld) fertig ...\n",
		pthread_self());
	return EXIT_SUCCESS;
}
