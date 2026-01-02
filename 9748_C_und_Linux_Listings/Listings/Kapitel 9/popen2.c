/* popen2.c */
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF1 255
#define BUF2 8192

static void
sendmail ( const char *to, const char *from,
		const char *subject,
		const char *inhalt ) {
	FILE *pipe, *pfad;
	char pfad_sendmail[BUF1];

	/* Wir ermitteln den Pfad zu sendmail. */
	pfad = popen ("which sendmail", "r");
	if (pfad == NULL) {
		perror("popen()");
		exit (EXIT_FAILURE);
	}
	fscanf (pfad, "%s", pfad_sendmail);
	pclose (pfad);
	strcat (pfad_sendmail, " -n -oi -t");

	/* Der Pfad ist meistens /usr/sbin/sendmail. */
	pipe = popen (pfad_sendmail, "w");
	if (pipe == NULL) {
		fprintf (stderr,
			"Konnte keine Verbindung zu sendmail aufbauen!n");
		exit (EXIT_FAILURE);
	}

	/* In sendmail schreiben ... */
	fprintf(pipe, "From:%s" "To:%s", from, to);
	/* if(cc != NULL){ fprintf(pipe, "Cc: %s\n", cc); } */
	/* if(bcc != NULL){ fprintf(pipe, "Bcc: %s\n", bcc); } */
	if(subject != NULL) {
		fprintf(pipe, "Subject:%s", subject);
	}

	/* Extra-Newline vorher ist hier wichtig ... */
	if(inhalt != NULL) { fprintf(pipe, "\n%s\n", inhalt); }
	pclose (pipe);
	printf ("Mail wurde versendet an : %s\n", to);
	return;
}

int main (int argc, char **argv) {
	char to[BUF1], from[BUF1], sub[BUF1],
		inhalt[BUF2], puffer[BUF1];

	printf ("Mail To   : ");
	fgets (to, BUF1, stdin);
	printf ("Mail from : ");
	fgets (from, BUF1, stdin);
	printf ("Betreff   : ");
	fgets (sub, BUF1, stdin);
	sub[strlen(sub)-1] = '\0';
	inhalt[0] = '\0';
	printf ("Inhalt    (beenden mit STRG+D) \n>");
	while (fgets (puffer, BUF1-1, stdin) != NULL) {
		if( strlen(inhalt) + strlen(puffer) < BUF2 ) {
			strcat (inhalt, puffer);
			printf (">");
		}
		else
			break;
	}
	inhalt[BUF2] = '\0';
	sendmail (to, from, sub, inhalt);
	return EXIT_SUCCESS;
}
