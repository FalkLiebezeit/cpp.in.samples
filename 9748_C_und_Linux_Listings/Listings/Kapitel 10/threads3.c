/* threads3.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_THREADS 5
#define BUF 255

/* Globale Variable mit Thread-IDs *
* für alle Threads sichtbar       */
static pthread_t th[MAX_THREADS];

static void aktion(void *name) {
	while( 1 ) {
		if(pthread_equal(pthread_self(),th[0])) {
			printf("\t->(%ld): Aufgabe \"abc\" A usführen ausführen \n",
				pthread_self());
			break;
		}
		else if(pthread_equal(pthread_self(),th[1])) {
			printf("\t->(%ld): Aufgabe \"efg\" aAusführen \n",
				pthread_self());
			break;
		}
		else if(pthread_equal(pthread_self(),th[2])) {
			printf("\t->(%ld): Aufgabe \"jkl\" aAusführen \n",
				pthread_self());
			break;
		}
		else {
			printf("\t->(%ld): Aufgabe \"xyz\" aAusführen \n",
				pthread_self());
			break;
		}
	}
	pthread_exit((void *)pthread_self());
}

int main (void) {
	int i;
	static int ret[MAX_THREADS];

	printf("->Haupt-Thread (ID:  %ld) gestartet...\n",
		pthread_self());
	/* Threads erzeugen */
	for (i = 0; i < MAX_THREADS; i++) {
		if (pthread_create (&th[i],NULL,&aktion,NULL) != 0) {
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
