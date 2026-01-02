/* semaphor.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define LOCK       -1
#define UNLOCK      1
#define PERM 0666 /* Zugriffsrechte */
#define KEY  123458L

static struct sembuf semaphore;
static int semid;

static int init_semaphore (void) {
	/* testen, ob das Semaphor bereits existiert */
	semid = semget (KEY, 0, IPC_PRIVATE);
	if (semid < 0) {
		/* ... existiert noch nicht, also anlegen */
		/* alle Zugriffsrechte der Dateikreierungsmaske */
		/* erlauben */
		umask(0);
		semid = semget (KEY, 1, IPC_CREAT | IPC_EXCL | PERM);
		if (semid < 0) {
			printf ("Fehler beim Anlegen des Semaphors ...\n");
			return -1;
		}
		printf ("(angelegt) Semaphor-ID : %d\n", semid);
		/* Semaphor mit 1 initialisieren */
		if (semctl (semid, 0, SETVAL, (int) 1) == -1)
			return -1;
	}
	return 1;
}

static int semaphore_operation (int op) {
	semaphore.sem_op = op;
	semaphore.sem_flg = SEM_UNDO;
	if( semop (semid, &semaphore, 1) == -1) {
		perror(" semop ");
		exit (EXIT_FAILURE);
	}
	return 1;
}

int main (void) {
	int res;

	res = init_semaphore ();
	if (res < 0)
		return EXIT_FAILURE;

	printf ("Vor dem kritischen Codeausschnitt ...\n");
	semaphore_operation ( LOCK );
	/* kritischer Codeausschnitt */
	printf ("PID %d verwendet Semaphor %d\n",
		getpid(), semid);
	printf ("Im kritischen Codeabschnitt ...\n");
	sleep (10);
	semaphore_operation ( UNLOCK );
	printf ("Nach dem kritischen Codeausschnitt ...\n");
	//semctl (semid, 0, IPC_RMID, 0);
	return EXIT_SUCCESS;
}
