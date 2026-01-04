/* thread2.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* insg. MAX_THREADS Threads erzeugen */
#define MAX_THREADS 3
#define BUF 255

/* Einfache Daten für die Wertübergabe an den Thread */
struct data {
	int wert;
	char msg[BUF];
};

/* Die Thread-Funktion */
static void *mythread (void *arg) {
	struct data *f= (struct data *)arg;
	/* Zufallszahl zwischen 1 und 10 (Spezial) */
	f->wert =  1+(int) (10.0*rand()/(RAND_MAX+1.0));
	snprintf (f->msg, BUF, "Ich bin Thread Nr. %ld",
		pthread_self());
	/* Thread beenden - Als als Rückgabewert Strukturdaten
	* verwenden - Alternativ alternativ auch pthread_exit( f );  */
	return arg;
}

int main (void) {
	pthread_t th[MAX_THREADS];
	int i;
	struct data *ret[MAX_THREADS];

	/* Haupt-Thread gestartet */
	printf("\n-> Main-Thread gestartet (ID:  %ld)\n",
		pthread_self());
	/* Speicher reservieren */
	for (i = 0; i < MAX_THREADS; i++){
		ret[i] = (struct data *)malloc(sizeof(struct data));
		if(ret[i] == NULL) {
			printf("Konnte keinen Speicher reservieren ...!\n");
			exit(EXIT_FAILURE);
		}
	}
	/* MAX_THREADS erzeugen */
	for (i = 0; i < MAX_THREADS; i++) {
		/* Jetzt Thread erzeugen */
		if(pthread_create(&th[i],NULL,&mythread,ret[i]) !=0) {
			fprintf (stderr, "Konnte Thread nicht erzeugen\n");
			exit (EXIT_FAILURE);
		}
	}
	/* Auf das Ende der Threads warten */
	for( i=0; i < MAX_THREADS; i++)
		pthread_join(th[i], (void **)&ret[i]);

	/* Daten ausgeben */
	for( i=0; i < MAX_THREADS; i++) {
		printf("Main-Thread: Daten empfangen: \n");
		printf("\t\twert = \"%d\"\n", ret[i]->wert);
		printf("\t\tmsg  = \"%s\"\n", ret[i]->msg);
	}
	/* Haupt-Thread ist jetzt auch fertig */
	printf("<- Main-Thread beendet (ID:  %ld)\n",
		pthread_self());
	return EXIT_SUCCESS;
}
