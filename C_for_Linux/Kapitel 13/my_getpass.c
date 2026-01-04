/* my_getpass.c */
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#define PASS 8

static char *my_getpass (void) {
	struct termios origstate, changedstate, teststate;
	char passwort[PASS];
	char *p = passwort;

	/* alten Terminalzustand speichern (von stdin = id 0) */
	if (tcgetattr (0, &origstate) != 0)
		printf ("tcgetattr failed");
	changedstate = origstate;

	/* neuen Terminalzustand setzen (von stdin = id 0) */
	/* Ausgabe ausschalten */
	changedstate.c_lflag &= ~ECHO;
	/* Newline beachten (einschalten) */
	changedstate.c_lflag |= ECHONL;

	if (tcsetattr (0, TCSANOW, &changedstate) != 0)
		printf ("tcsetattr failed");

	/* Überprüfenüberprüfen, ob der Terminalzustand erfolgreich */
	/* verändert wurde                                */
	tcgetattr (0, &teststate);
	if (teststate.c_lflag & ECHO)
		printf ("ECHO-Flag konnte nicht abgeschaltet werden\n");
	if (!teststate.c_lflag & ECHONL)
		printf ("ECHONL konnte nicht eingeschaltet werden\n");

	fprintf(stdout,"Passwort eingeben : ");
	fgets(passwort, PASS, stdin);

	/* alten Terminalzustand wiederherstellen */
	/* (von stdin = id 0)                     */
	if (tcsetattr (0, TCSANOW, &origstate) != 0)
		printf ("tcsetattr failed");
	return p;
}

int main (void) {
	char *ptr = my_getpass();
	printf("Ihre Eingabe war: %s\n",ptr);
	return EXIT_SUCCESS;
}
