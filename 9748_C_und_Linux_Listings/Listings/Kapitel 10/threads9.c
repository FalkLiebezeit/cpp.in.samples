/* threads9.c */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int werte[10];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void thread1 (void *arg) {
	int ret, i;

	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());
	sleep (1);
	ret = pthread_mutex_lock (&mutex);
	if (ret != 0) {
		printf ("Fehler bei lock in Thread:%ld\n",
			pthread_self());
		exit (EXIT_FAILURE);
	}

	/* Kritischer Codeabschnitt */
	for (i = 0; i < 10; i++)
		werte[i] = i;
	/* Kritischer Codeausschnitt Ende */

	printf ("\t->Thread %ld sendet Bedingungsvariable\n",
		pthread_self());
	pthread_cond_signal (&cond);

	ret = pthread_mutex_unlock (&mutex);
	if (ret != 0) {
		printf ("Fehler bei unlock in Thread: %ld\n",
			pthread_self ());
		exit (EXIT_FAILURE);
	}
	printf ("\t->Thread %ld ist fertig\n",pthread_self());
	pthread_exit ((void *) 0);
}

static void thread2 (void *arg) {
	int i;
	int summe = 0;

	printf ("\t->Thread %ld wartet auf Bedingungsvariable\n",
		pthread_self ());
	pthread_cond_wait (&cond, &mutex);
	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());
	for (i = 0; i < 10; i++)
		summe += werte[i];
	printf ("\t->Thread %ld fertig\n",pthread_self());
	printf ("Summe aller Zahlen beträgt: %d\n", summe);
	pthread_exit ((void *) 0);
}

int main (void) {
	pthread_t th[2];

	printf("->Main-Thread %ld gestartet\n", pthread_self());

	pthread_create (&th[0], NULL, thread1, NULL);
	pthread_create (&th[1], NULL, thread2, NULL);

	pthread_join (th[0], NULL);
	pthread_join (th[1], NULL);

	printf("->Main-Thread %ld beendet\n", pthread_self());
	return EXIT_SUCCESS;
}
