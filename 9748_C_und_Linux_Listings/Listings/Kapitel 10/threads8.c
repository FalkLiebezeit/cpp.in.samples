/* threads8.c */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define THREAD_MAX 3

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *threads (void *arg) {
	printf("\t->Thread %ld wartet auf Bedingung\n",
		pthread_self());

	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);

	printf("\t->Thread %ld hat Bedingung erhalten\n",
		pthread_self());

	printf("\t->Thread %ld: Sende wieder die "
		"Bedingungsvariable\n", pthread_self());
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main (void) {
	int i;
	pthread_t th[THREAD_MAX];

	printf("->Main-Thread %ld gestartet\n", pthread_self());
	for(i=0; i<THREAD_MAX; i++)
		if (pthread_create (&th[i],NULL, &threads, NULL)!=0) {
			printf ("Konnte keinen Thread erzeugen\n");
			exit (EXIT_FAILURE);
		}
	printf("->Main-Thread: h abe Habe soeben %d Threads erzeugt\n",
		THREAD_MAX);

	/* Kurz warten,ruhig legen , damit der Main-Thread als Erstes die
	* Bedingungsvariable sendet */
	sleep(1);
	printf("->Main-Thread: Sende die Bedingungsvariable\n");
	pthread_cond_signal(&cond);

	for(i=0; i<THREAD_MAX; i++)
		pthread_join (th[i], NULL);
	printf("->Main-Thread %ld beendet\n", pthread_self());
	pthread_exit(NULL);
}
