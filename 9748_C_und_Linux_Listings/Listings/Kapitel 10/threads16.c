/* threads16.c */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 3

void thread_once(void) {
	printf("Funktion thread_once() aufgerufen\n");
}

void* thread_func (void* args) {
	printf("Thread %ld wurde gestartet\n", pthread_self());
	thread_once();
	printf("Thread %ld ist fertig gestartet\n",
		pthread_self());
	pthread_exit(NULL);
}

int main (void) {
	int i;
	pthread_t threads[MAX_THREADS];
	/* Threads erzeugen */
	for (i = 0; i < MAX_THREADS; ++i)
		pthread_create (&(threads[i]), NULL, thread_func, NULL);
	/* Auf die Threads warten  */
	for (i = 0; i < MAX_THREADS; ++i)
		pthread_join (threads[i], NULL);
	return EXIT_SUCCESS;
}
