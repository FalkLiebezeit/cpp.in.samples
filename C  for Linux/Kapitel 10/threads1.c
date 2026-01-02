/* threads1.c */
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

/* Ein einfacher Exit-Handler für Threads, der  *
* pthread_cleanup_push und pthread_cleanup_pop *
* in der Praxis demonstrieren soll             */
static void exit_handler_mem( void * arg ) {
	printf("\tExit-Handler aufgerufen ...");
	struct data *mem =  (struct data *)arg;
	/* Speicher freigeben */
	free(mem);
	printf("Speicher freigegeben\n");
}

/* Die Thread-Funktion */
static void mythread (void *arg) {
	struct data *f = (struct data *)arg;
	/* Exit-Handler einrichten - wird automatisch nach *
	* pthread_exit oder Thread-Ende aufgerufen        */
	pthread_cleanup_push( exit_handler_mem, (void*)f );
	/* Daten ausgeben */
	printf("\t-> Thread mit ID:  %ld gestartet\n",
		pthread_self());
	printf("\tDaten empfangen: \n");
	printf("\t\twert = \"%d\"\n", f->wert);
	printf("\t\tmsg  = \"%s\"\n", f->msg);
	/* Den Exit-Handler entfernen, aber trotzdem ausführen, *
	* da als Angabe 1 anstatt 0 verwendet wurde            */
	pthread_cleanup_pop( 1 );
	/* Thread beenden - Als als Rückgabewert Thread-ID verwenden.
	* Alternativ kann hierfür auch:
	* return(void) pthread_self();
	* verwendet werden */
	pthread_exit((void *)pthread_self());
}

int main (void) {
	pthread_t th[MAX_THREADS];
	struct data *f;
	int i;
	static int ret[MAX_THREADS];
	/* Haupt-Thread gestartet */
	printf("\n-> Main-Thread gestartet (ID:  %ld)\n",
		pthread_self());
	/* MAX_THREADS erzeugen */
	for (i = 0; i < MAX_THREADS; i++) {
		/* Speicher für Daten anfordern u. m. it Werten belegen */
		f = (struct data *)malloc(sizeof(struct data));
		if(f == NULL) {
			printf("Konnte keinen Speicher reservieren ...!\n");
			exit(EXIT_FAILURE);
		}
		/* Zufallszahl zwischen 1 und 10 (Spezial) */
		f->wert =  1+(int) (10.0*rand()/(RAND_MAX+1.0));
		snprintf (f->msg, BUF, "Ich bin Thread Nr. %d", i+1);
		/* Jetzt Thread erzeugen */
		if(pthread_create(&th[i], NULL, &mythread, f) != 0) {
			fprintf (stderr, "Konnte Thread nicht erzeugen\n");
			exit (EXIT_FAILURE);
		}
	}
	/* Auf das Ende der Threads warten */
	for( i=0; i < MAX_THREADS; i++)
		pthread_join(th[i], &ret[i]);
	/* Rückgabewert der Threads ausgeben */
	for( i=0; i < MAX_THREADS; i++)
		printf("<-Thread %ld ist fertig\n", ret[i]);
	/* Haupt-Thread ist jetzt auch fertig */
	printf("<- Main-Thread beendet (ID:  %ld)\n",
		pthread_self());
	return EXIT_SUCCESS;
}
