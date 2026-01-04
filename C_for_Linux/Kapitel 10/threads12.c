/* threads12.c */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

static int werte[10];
sem_t sem;

static void thread1 (void *arg) {
	int ret, i, val;

	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());

	/* Kritischer Codeabschnitt */
	for (i = 0; i < 10; i++)
		werte[i] = i;
	/* Kritischer Codeausschnitt Ende */

	/* Semaphor e um 1 inkrementieren */
	sem_post(&sem);
	/* Aktuellen Wert ermitteln */
	sem_getvalue(&sem, &val);
	printf("\t->Semaphore  inkrementiert (Wert: %d)\n", val);

	printf ("\t->Thread %ld ist fertig\n\n",pthread_self());
	pthread_exit ((void *) 0);
}

static void thread2 (void *arg) {
	int i;
	int summe = 0;

	/* Semaphor e suspendiert, bis der Wert ungleich 0 ist */
	sem_wait(&sem);

	printf ("\t->Thread %ld gestartet ...\n",
		pthread_self ());
	for (i = 0; i < 10; i++)
		summe += werte[i];

	printf ("\t->Summe aller Zahlen beträgt: %d\n", summe);
	printf ("\t->Thread %ld fertig\n\n",pthread_self());
	pthread_exit ((void *) 0);
}

int main (void) {
	pthread_t th[2];
	int val;

	printf("->Main-Thread %ld gestartet\n", pthread_self());
	/* Semaphore  initialisieren */
	sem_init(&sem, 0, 0);
	/* Aktuellen Wert abfragen */
	sem_getvalue(&sem, &val);
	printf("->Semaphor e  initialisiert (Wert: %d)\n\n", val);

	/* Mit Absicht anders herumumgekehrt */
	pthread_create (&th[1], NULL, thread2, NULL);
	pthread_create (&th[0], NULL, thread1, NULL);

	pthread_join (th[0], NULL);
	pthread_join (th[1], NULL);

	/* Aktuellen Wert abfragen */
	sem_getvalue(&sem, &val);
	printf("->Semaphore  Semaphor (Wert: %d)\n", val);
	/* Semphore löschen */
	sem_destroy(&sem);
	printf("->Semaphor e  gelöscht\n");
	printf("->Main-Thread %ld beendet\n", pthread_self());
	return EXIT_SUCCESS;
}
