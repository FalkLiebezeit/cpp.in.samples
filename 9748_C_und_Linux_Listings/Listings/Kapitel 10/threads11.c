/* threads11.c */
#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMTHREADS 2

static void checkResults (const char *string, int val) {
	if (val) {
		printf ("Fehler mit %d bei %s", val, string);
		exit (EXIT_FAILURE);
	}
}

static pthread_mutex_t dataMutex =
PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t DatenVorhandenCondition =
PTHREAD_COND_INITIALIZER;
static int DatenVorhanden = 0;
static int geteilteDaten  = 0;

static void *theThread (void *parm) {
	int rc;
	// Datenpaket in zwei Verarbeitungsschritten
	int retries = 2;

	printf ("\t->Client %ld: gestartet\n", pthread_self ());
	rc = pthread_mutex_lock (&dataMutex);
	checkResults ("pthread_mutex_lock()\n", rc);

	while (retries--) {
		while (!DatenVorhanden) {
			printf ("\t->Client %ld: Warte auf Daten ...\n",
				pthread_self ());
			rc = pthread_cond_wait ( &DatenVorhandenCondition,
								&dataMutex);
			if (rc) {
				printf ("Client %ld: pthread_cond_wait()"
					" Fehler rc=%d\n", rc, pthread_self ());
				pthread_mutex_unlock (&dataMutex);
				exit (EXIT_FAILURE);
			}
		}
		printf("\t->Client %ld: Daten wurden gemeldet --->\n"
			"\t----> Bearbeite die Daten, solange sie "
			"geschützt sind (lock)\n", pthread_self ());
		if (geteilteDaten == 0) {
			DatenVorhanden = 0;
		}
	}// Ende while(retries--)

	printf ("Client %ld: Alles erledigt\n",
		pthread_self ());
	rc = pthread_mutex_unlock (&dataMutex);
	checkResults ("pthread_mutex_unlock()\n", rc);
	return NULL;
}

int main (int argc, char **argv) {
	pthread_t thread[NUMTHREADS];
	int rc = 0;
	// Gesamtanzahl der Datenpakete
	int anzahlDaten = 4;
	int i;
	printf ("->Main-Thread %ld gestartet ...\n");
	for (i = 0; i < NUMTHREADS; ++i) {
		rc=pthread_create (&thread[i], NULL, theThread, NULL);
		checkResults ("pthread_create()\n", rc);
	}

	/* Servers-Schleife  */
	while (anzahlDaten--) {
		sleep (3); // Eine Bremse zum "Mitverfolgen"
		printf ("->Server: Daten gefunden\n");

	/* Schütze geteilte (shared) Daten und Flags */
	rc = pthread_mutex_lock (&dataMutex);
	checkResults ("pthread_mutex_lock()\n", rc);
	printf ("->Server: Sperre die Daten und gib eine "
		"Meldung an Consumer\n");
	++geteilteDaten;     /* Füge "shared" Daten hinzu  */
	DatenVorhanden = 1;  /* ein vorhandenes Datenpaket */
	/* Client wieder aufwecken */
	rc = pthread_cond_signal (&DatenVorhandenCondition);
	if (rc) {
		pthread_mutex_unlock (&dataMutex);
		printf ("Server: Fehler beim Aufwecken von "
			"Client, rc=%d\n", rc);
		exit (EXIT_FAILURE);
	}
	printf("->Server: Gibt die gesperrten Daten"
		" wieder frei\n");
	rc = pthread_mutex_unlock (&dataMutex);
	checkResults ("pthread_mutex_lock()\n", rc);
	}// Ende while(anzahlDaten--)
	for (i = 0; i < NUMTHREADS; ++i) {
		rc = pthread_join (thread[i], NULL);
		checkResults ("pthread_join()\n", rc);
	}
	printf ("->Main-Thread ist fertig\n");
	return EXIT_SUCCESS;
}
