/* threads7.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#define BUF 255

struct data {
	FILE *fz;
	char filename[BUF];
	pthread_mutex_t mutex;
};

static void thread_schreiben(void *arg) {
	char string[BUF];
	struct data *d=(struct data *)arg;

	printf("Bitte Eingabe machen: ");
	fgets(string, BUF, stdin);
	fputs(string, d->fz);
	fflush(d->fz);

	/* Mutex wieder freigeben */
	pthread_mutex_unlock( &d->mutex );
	/* Thread-Ende */
	pthread_exit((void *)pthread_self());
}

static void thread_lesen(void *arg) {
	char string[BUF];
	struct data *d=(struct data *)arg;

	/* Mutex sperren */
	while( (pthread_mutex_trylock( &d->mutex )) == EBUSY) {
		sleep(10);
		printf("Lese-Thread wartet auf Arbeit ...\n");
		printf("Bitte Eingabe machen: ");
		fflush(stdout);
	}
	rewind(d->fz);
	fgets(string, BUF, d->fz);
	printf("Ausgabe Thread %ld: ", pthread_self());
	fputs(string, stdout);
	fflush(stdout);
	/* Mutex wieder freigeben */
	pthread_mutex_unlock( &d->mutex );
	/* Thread-Ende */
	pthread_exit((void *)pthread_self());
}

int main (void) {
	static pthread_t th1, th2;
	static int ret1, ret2;
	struct data *d;

	/* Speicher für die Struktur reservieren */
	d = malloc(sizeof(struct data));
	if(d == NULL) {
		printf("Konnte keinen Speicher reservieren ...!\n");
		exit(EXIT_FAILURE);
	}

	printf("->Haupt-Thread (ID:  %ld) gestartet ...\n",
		pthread_self());

	strncpy(d->filename, "testfile", BUF);
	d->fz = fopen( d->filename, "w+" );
	if( d->fz == NULL ) {
		printf("Konnte Datei %s nicht öffnen\n", d->filename);
		exit(EXIT_FAILURE);
	}

	/* Mutex initialisieren */
	pthread_mutex_init( &d->mutex, NULL );
	/* Mutex sperren */
	pthread_mutex_lock( &d->mutex );

	/* Threads erzeugen */
	if(pthread_create (&th1,NULL,&thread_schreiben,d) != 0) {
		fprintf (stderr, "Konnte keinen Thread erzeugen\n");
		exit (EXIT_FAILURE);
	}

	/* Threads erzeugen */
	if (pthread_create (&th2,NULL, &thread_lesen, d) != 0) {
		fprintf (stderr, "Konnte keinen Thread erzeugen\n");
		exit (EXIT_FAILURE);
	}
	pthread_join(th1, &ret1);
	pthread_join(th2, &ret2);

	/* Dynamisch angelegten Mutex löschen */
	pthread_mutex_destroy( &d->mutex );

	printf("<-Thread %ld fertig\n", th1);
	printf("<-Thread %ld fertig\n", th1);
	printf("<-Haupt-Thread (ID:  %ld) fertig ...\n",
		pthread_self());
	return EXIT_SUCCESS;
}
