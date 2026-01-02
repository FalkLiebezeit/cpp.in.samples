/* threads18.c */
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

pthread_t tid2;

void int_handler(int dummy) {
	printf("SIGINT erhalten von TID(%d)\n", pthread_self());
}

void usr1_handler(int dummy) {
	printf("SIGUSR1 erhalten von TID(%d)\n", pthread_self());
}

void *thread_1(void *dummy) {
	int sig, status, *status_ptr = &status;
	sigset_t sigmask;

	/* Kein Signal blockieren - SIG_UNBLOCK */
	sigfillset(&sigmask);
	pthread_sigmask(SIG_UNBLOCK, &sigmask, (sigset_t *)0);
	sigwait(&sigmask, &sig);

	switch(sig) {
		case SIGINT: int_handler(sig); break;
		default   : break;
	}
	printf("TID(%d) sende SIGINT an %d\n",
		pthread_self(), tid2);
	/* blockiert von tid2 */
	pthread_kill(tid2, SIGINT);
	printf("TID(%d) sende SIGUSR1 an %d\n",
		pthread_self(), tid2);
	/* nicht blockiert von tid2 */
	pthread_kill(tid2, SIGUSR1);

	pthread_join(tid2, (void **)status_ptr);
	printf("TID(%d) Exit-Status = %d\n", tid2, status);

	printf("TID(%d) wird beendet\n", pthread_self());
	pthread_exit((void *)NULL);
}

void *thread_2(void *dummy) {
	int sig;
	sigset_t sigmask;

	/* Alle Bits auf null setzen */
	sigemptyset(&sigmask);
	/* Signal SIGUSR1 nicht blockieren ... */
	sigaddset(&sigmask, SIGUSR1);
	pthread_sigmask(SIG_UNBLOCK, &sigmask, (sigset_t *)0);
	sigwait(&sigmask, &sig);

	switch(sig) {
		case SIGUSR1 : usr1_handler(sig); break;
		default : break;
	}
	printf("TID(%d) wird beendet\n", pthread_self());

	pthread_exit((void *)99);
}

int main(void) {
	pthread_t tid1;
	pthread_attr_t attr_obj;
	void *thread_1(void *), *thread_2(void *);
	sigset_t sigmask;
	struct sigaction action;

	/* Signalmaske einrichten - alle Signale im *
	* Haupt-Thread blockieren */
	sigfillset(&sigmask);       /* Alle Bits ein ...*/
	pthread_sigmask(SIG_BLOCK, &sigmask, (sigset_t *)0);

	/* Setup Signal-Hhandler für SIGINT & SIGUSR1 */
	action.sa_flags = 0;
	action.sa_handler = int_handler;
	sigaction(SIGINT, &action, (struct sigaction *)0);
	action.sa_handler = usr1_handler;
	sigaction(SIGUSR1, &action, (struct sigaction *)0);

	pthread_attr_init(&attr_obj);
	pthread_attr_setdetachstate( &attr_obj,
		PTHREAD_CREATE_DETACHED );
	pthread_create(&tid1, &attr_obj, thread_1, (void *)NULL);
	printf("TID(%d) erzeugt\n", tid1);
	pthread_attr_setdetachstate( &attr_obj,
		PTHREAD_CREATE_JOINABLE);
	pthread_create(&tid2, &attr_obj, thread_2, (void *)NULL);
	printf("TID(%d) erzeugt\n", tid2);

	sleep(1); // Kurze Pause ...

	printf("Haupt-Thread(%d) sendet SIGINT an TID(%d)\n",
		pthread_self(), tid1);
	pthread_kill(tid1, SIGINT);
	printf("Haupt-Thread(%d) sendet SIGUSR1 an TID(%d)\n",
		pthread_self(), tid1);
	pthread_kill(tid1, SIGUSR1);

	printf("Haupt-Thread(%d) wird beendet\n",
		pthread_self());
	// Beendet nicht den Prozess!!!
	pthread_exit((void *)NULL);
}
