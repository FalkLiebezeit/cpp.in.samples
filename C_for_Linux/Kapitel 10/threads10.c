/* threads10.c */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct data {
	int werte[10];
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

static void thread1 (void *arg) {
	struct data *d=(struct data *)arg;
	int ret, i;

	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());
	sleep (1);
	ret = pthread_mutex_lock (&d->mutex);
	if (ret != 0) {
		printf ("Fehler bei lock in Thread:  %ld\n",
			pthread_self());
		exit (EXIT_FAILURE);
	}

	/* Kritischer Codeabschnitt */
	for (i = 0; i < 10; i++)
		d->werte[i] = i;
	/* Kritischer Codeausschnitt Ende */

	printf ("\t->Thread %ld sendet Bedingungsvariable\n",
		pthread_self());
	pthread_cond_signal (&d->cond);

	ret = pthread_mutex_unlock (&d->mutex);
	if (ret != 0) {
		printf ("Fehler bei unlock in Thread: %ld\n",
			pthread_self ());
		exit (EXIT_FAILURE);
	}
	printf ("\t->Thread %ld ist fertig\n", pthread_self());
	pthread_exit ((void *) 0);
}

static void thread2 (void *arg) {
	struct data *d=(struct data *)arg;
	int i;
	int summe = 0;

	printf ("\t->Thread %ld wartet auf Bedingungsvariable\n",
		pthread_self ());
	pthread_cond_wait (&d->cond, &d->mutex);
	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());
	for (i = 0; i < 10; i++)
		summe += d->werte[i];
	printf ("\t->Thread %ld fertig\n",pthread_self());
	printf ("Summe aller Zahlen beträgt: %d\n", summe);
	pthread_exit ((void *) 0);
}

int main (void) {
	pthread_t th[2];
	struct data *d;
	/* Speicher für die Struktur reservieren */
	d = malloc(sizeof(struct data));
	if(d == NULL) {
		printf("Konnte keinen Speicher reservieren ...!\n");
		exit(EXIT_FAILURE);
	}

	/* Bedingungsvariablen initialisieren */
	pthread_cond_init(&d->cond, NULL);
	printf("->Main-Thread %ld gestartet\n", pthread_self());
	pthread_create (&th[0], NULL, thread1, d);
	pthread_create (&th[1], NULL, thread2, d);
	pthread_join (th[0], NULL);
	pthread_join (th[1], NULL);
	/* Bedingungsvariable freigeben */
	pthread_cond_destroy(&d->cond);
	printf("->Main-Thread %ld beendet\n", pthread_self());
	return EXIT_SUCCESS;
}
