/* server_shm.c */
#include "shm_header.h"
static void delete (void) {
	int res;
	printf ("\nServer wird beendet - Lösche Semaphore %d.\n",DeleteSemid);
	if (semctl (DeleteSemid, 0, IPC_RMID, 0) == -1) {
		printf ("Fehler beim Löschen der Semaphore.\n");
	}
	/* Wenn Serverprozess beendet wird - */
	/* Segment automatisch löschen */
	res = shmctl (DeleteShmid, IPC_RMID, NULL);
	if (res == -1)
		printf ("Fehler bei shmctl() shmid %d, Kommando %d\n",DeleteShmid, IPC_RMID);
	return;
}

static void sigdelete (int signum) {
	exit(EXIT_FAILURE);
}

static void server (void) {
	union semun sunion;
	int semid, shmid;
	int res;
	void *shmdata;
	char *buffer;

	/* Eine Semaphore erstellen */
	semid = safesemget (IPC_PRIVATE, 2, SHM_R | SHM_W);
	DeleteSemid = semid;
	/* Semaphore beim Beenden entfernen */
	atexit (&delete);
	/* Signalhandler einrichten */
	my_signal (SIGINT, &sigdelete);

	/* Semaphore initialisieren */
	sunion.val = 1;
	safesemctl (semid, SN_EMPTY, SETVAL, sunion);
	sunion.val = 0;
	safesemctl (semid, SN_FULL, SETVAL, sunion);

	/* Ein Shared-Memory-Segment einrichten */
	shmid = shmget (IPC_PRIVATE, SHMDATASIZE,IPC_CREAT | SHM_R | SHM_W);
	if (shmid == -1)
		printf ("Fehler bei key %d, mit der Größe %d\n",IPC_PRIVATE, SHMDATASIZE);

	DeleteShmid = shmid;

	/* Shared-Memory-Segment anbinden */
	shmdata = shmat (shmid, NULL, 0);
	if (shmdata == (void *) -1)
		printf ("Fehler bei shmat(): shmid %d\n", shmid);

	/* Kennung am Anfang des Segments schreiben */
	*(int *) shmdata = semid;
	buffer = shmdata + sizeof (int);

	printf ("Server läuft mit Shared-Memory-ID %d\n", shmid);

	while (1) {
		printf ("Warte ...");
		fflush (stdout);
		/* Sperren und Warten */
		locksem (semid, SN_FULL);
		printf ("\n... fertig.\n");
		/* Ein Client hat etwas geschrieben */
		printf ("Nachricht erhalten: %s\n", buffer);
		/* Sperre aufheben */
		unlocksem (semid, SN_EMPTY);
	}
	return;
}

int main (int argc, char **argv) {
	server ();
	printf("--- Server-Ende ---\n");
	return EXIT_SUCCESS;
}
