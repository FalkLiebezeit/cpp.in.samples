/* add_db.c
 * Eine Gedächtnisstütze:
mysql> create database news;
mysql> use news;
mysql> create table data( datum TIMESTAMP, autor VARCHAR(200),
    -> suche VARCHAR(200), title VARCHAR(150), beschreibung BLOB,
    -> inhalt BLOB);
mysql> INSERT INTO data (autor, title, suche, beschreibung,
    -> inhalt)
    -> VALUES (
    -> "Jürgen Wolf", "Ein Testtitel", "suchwörter test titel",
    -> "Beispiel, wie man mit MySQL und der C-API ein eigenes
    -> Newssystem erstellt",
    -> "Der eigentliche Inhalt nach den Schlagzeilen zum Thema
    -> MySQL und der C-API");
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#define MAX 255
#define BUFFER 4096
#include "my_cgi.h"

enum { HOST, USER, PASSWORT, DATENBANK,
       AUTOR, TITLE, SUCHE, BESCHREIBUNG, INHALT};
static char *param[9];

static int fetch_data( void ) {
	int i;
	char *str;
	struct CGI_DATEN *cgi;
	/* Für Fehlermeldungen */
	printf("Content-Type: text/html\n\n");
	/* Eingabe einlesen */
	str = getdata();
	if(str == NULL) {
		printf("Fehler beim Einlesen der Formulareingabe");
		return 0;
	}
	/* Hexzeichen in ASCII-Zeichen konvertieren und aus '+' */
	/* Leerzeichen machen                                   */
	hex2ascii(str);
	/* Liste der Formulardaten erstellen */
	cgi = erstellen(str);
	if (cgi == NULL) {
		printf("Fehler beim Erstellen der ""Variablen/Werteliste!!\n");
		return 0;
	}
	for( i = 0; i < 9; i++ ) {
		param[i] = cgi->wert;
		cgi = cgi->next;
	}
	return 1;
}

/* Mit dem MySQL-Server und den entsprechenden */
/*  Verbindungsdaten eine Verbindung herstellen */
static int mein_connect (MYSQL * my) {
	/* Mit dem Server verbinden */
	if (mysql_real_connect (my,   /* Zeiger auf MYSQL-Handler */
	param[HOST],         /* Hostname */
	param[USER],         /* User-Name */
	param[PASSWORT],     /* Passwort für user_name */
	param[DATENBANK],    /* Name der Datenbank */
	0,        /* Port (default=0) */
	NULL,    /* Socket (default=NULL) */
	0 /* keine Flags */ ) ==    NULL) {
		fprintf (stdout, "Fehler mysql_real_connect():""%u (%s)\n", mysql_errno (my), mysql_error (my));
		exit (EXIT_FAILURE);
	}
	return 1;
}

static void insert_into_db( MYSQL *my ) {
	char buf[8192];
	/* Tabelle */
	sprintf(buf, "INSERT INTO data (autor, title, suche, "
	"beschreibung, inhalt)"
	" VALUES (\'%s\','\%s\','\%s\', '\%s\', \'%s\');"
	,param[AUTOR], param[TITLE], param[SUCHE],
	param[BESCHREIBUNG], param[INHALT]);
	/* printf("%s\n", buf); */
	if(mysql_real_query(my, buf, strlen(buf)) !=0) {
		fprintf (stdout, "Fehler mysql_real_connect():""%u (%s)\n", mysql_errno (my), mysql_error (my));
		exit (EXIT_FAILURE);
	}
}

/* Speicher freigeben und Verbindung beenden */
static void clean_up_shutdown (MYSQL * my) {
	mysql_close (my);
}

int main (int argc, char **argv) {
	MYSQL *my;
	/* Daten abholen und für die Eintragung vorbereiten */
	fetch_data();
	/* Handle initialisieren */
	my = mysql_init (NULL);
	if (my == NULL) {
		fprintf (stderr, " Initialisierung fehlgeschlagen\n");
		exit (EXIT_FAILURE);
	}
	/* Mit dem Server verbinden */
	if (mein_connect (my) != -1)
		printf ("Erfolgreich mit dem MySQL-Server verbunden\n");
	/* Daten in die Datenbank schreiben */
	insert_into_db( my );

	printf("Eintragung erfolgreich<br>Zur Indexseite geht´s "
	"<a href=\"http://localhost/cgi-bin/index_news\">hier </a>"
	" und für weitere Artikel klicken Sie bitte"
	" <a href=\"http://localhost/login.html\">hier</a>\n");

	clean_up_shutdown( my );
	return EXIT_SUCCESS;
}

