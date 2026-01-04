/* threads13.c */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

pthread_t t1, t2, t3;
static int zufallszahl;

static void cancel_test1 (void) {
	/* Pseudo-Ssynchronisation, damit nicht ein Thread
	beendet wird, der noch gar nicht läuft. */
	sleep(1);
	if (zufallszahl > 25) {
		pthread_cancel (t3);
		printf ("(%d) : Thread %ld beendet %ld\n",
			zufallszahl, pthread_self(), t3);
		printf ("%ld zu Eende \n", pthread_self());
		pthread_exit ((void *) 0);
	}
}

static void cancel_test2 (void) {
	sleep(1);  // Pseudo-Ssynchronisation
	if (zufallszahl <= 25) {
		pthread_cancel (t2);
		printf ("(%d) : Thread %ld beendet %ld\n",
			zufallszahl, pthread_self(), t2);
		printf ("%ld zu Eende \n", pthread_self());
		pthread_exit ((void *) 0);
	}
}

static void zufall (void) {
	srand (time (NULL));
	zufallszahl = rand () % 50;
	pthread_exit (NULL);
}

int main (void) {
	if ((pthread_create (&t1, NULL, zufall, NULL)) != 0) {
		fprintf (stderr, "Fehler bei ptread_create ...\n");
		exit (EXIT_FAILURE);
	}
	if((pthread_create(&t2, NULL, cancel_test1, NULL))!=0) {
		fprintf (stderr, "Fehler bei ptread_create...\n");
		exit (EXIT_FAILURE);
	}
	if((pthread_create(&t3, NULL, cancel_test2, NULL))!=0) {
		fprintf (stderr, "Fehler bei ptread_create ...\n");
		exit (EXIT_FAILURE);
	}
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	pthread_join (t3, NULL);
	return EXIT_SUCCESS;
}
