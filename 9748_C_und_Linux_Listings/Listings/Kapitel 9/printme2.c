/* printme2.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF1 254
#define BUF2 8192

void an_den_drucker (const char *);
static void sendmail (const char *, const char *, const char *, const char *); // static (Dämonprozess)

static void
sendmail ( const char *to, const char *from,
		const char *subject,
		/* const char *cc, const char *bcc, */
		const char *inhalt ) { // static (Dämonprozess)
	FILE *pipe, *pfad;
	char pfad_sendmail[BUF1];
	char protokoll[BUF2+BUF2];

	protokoll[0] = '\0';
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
		perror("popen()");
		exit (EXIT_FAILURE);
	}

	/* In sendmail schreiben ... */
	fprintf(pipe, "From:%s" "To:%s", from, to);
	strcat(protokoll, "From: ");
	strcat(protokoll, from);
	strcat(protokoll, "\nTo: ");
	strcat(protokoll, to);
	/* if(cc != NULL) {
		fprintf(pipe, "Cc: %s\n", cc);
		strcat(protokoll, "\nCc: ");
		strcat(protokoll, cc);
	}*/
	/* if(bcc != NULL) {
		fprintf(pipe, "Bcc: %s\n", bcc);
		strcat(protokoll, "\nBcc: ");
		strcat(protokoll, bcc);
	}*/
	if(subject != NULL) {
		fprintf(pipe, "Subject:%s", subject);
		strcat(protokoll, "\nSubject: ");
		strcat(protokoll, subject);
	}
	strcat(protokoll, "\n\n");
	if(inhalt != NULL) {
		fprintf(pipe, "\n%s\n", inhalt);
		strcat(protokoll, inhalt);
		strcat(protokoll, "\n");
	}
	pclose (pipe);
	printf ("Mail wurde erfolgreich versendet an: %s\n", to);
	an_den_drucker (protokoll);
	return;
}

void an_den_drucker (char *text) {
	FILE *p;
	/* Pipe zum Tool lpr erstellen zum Schreiben auf lpr */
	p = popen ("lpr", "w");
	if (p == NULL) {
		perror("popen()");
		exit (EXIT_FAILURE);
	}

	/* an den Drucker schreiben */
	printf ("Sende Auftrag an den Drucker ...\n");
	fprintf (p, "%s", text);
	pclose (p);
	return;
}

int main (int argc, char **argv) {
	char to[BUF1], from[BUF1], sub[BUF1],
		inhalt[BUF2], puffer[BUF1];

	printf ("Mail to   : ");
	fgets (to, BUF1, stdin);
	printf ("Mail from : ");
	fgets (from, BUF1, stdin);
	printf ("Betreff   : ");
	fgets (sub, BUF1, stdin);
	sub[strlen(sub)-1] = '\0';
	inhalt[0] = '\0';

	printf ("Inhalt    (beenden mit STRG+D) \n>");
	while (fgets (puffer, BUF1, stdin) != NULL) {
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

