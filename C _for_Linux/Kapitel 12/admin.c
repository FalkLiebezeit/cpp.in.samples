/* admin.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "my_cgi.h"
#define MAX 255
#define BUFFER 4096
static char *connect_param[4];

static int fetch_login_db( void ) {
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
	for( i = 0; i < 4; i++ ) {
		connect_param[i] = cgi->wert;
		cgi = cgi->next;
	}
	return 1;
}

static void print_admin_input( void ) {
	char buf[BUFFER];
	sprintf(buf,"<h1>Eintragen von neuen Artikeln</h1>"
	"<form action=\"http://localhost/cgi-bin/add_db\"  "
	"method=\"POST\">"
	"<input type=\"hidden\"  name=\"host\"  value=\"%s\">"
	"<input type=\"hidden\"  name=\"user\"  value=\"%s\">"
	"<input type=\"hidden\"  name=\"passwort\"  value=\"%s\">"
	"<input type=\"hidden\"  name=\"datenbank\"  value=\"%s\">"
	"<pre>Autor: <input type=\"text\"  name=\"autor\"  "
	"value=\"Admin\"  size=30><br>"
	"Titel: <input type=\"text\"  name=\"titel\"  size=30><br>"
	"Schlüsselworte zur Suche :\n"
	"<input type=\"text\"  name=\"suche\"  value=\"Suchwörter\""
	" size=50><br>"
	"Schlagzeilen für die Hauptseite :\n"
	"<textarea name=\"beschreibung\"  cols=\"50\"  "
	"rows=\"6\"></textarea><br>"
	"Rest vom Artikel :\n"
	"<textarea name=\"beschreibung\"  cols=\"50\"  "
	"rows=\"6\"></textarea><br>"
	"<input type=\"submit\"  value=\"Abschicken\"><input "
	"type=\"reset\"  value=\"Zurücksetzen\"></pre></form>",
	connect_param[0],connect_param[1],connect_param[2],
	connect_param[3]);
	printf("%s",buf);
}

int main (int argc, char **argv) {
	/* Login-Daten für die Datenbank abholen */
	fetch_login_db( );
	/* Eingabeformular für Admin ausgeben */
	print_admin_input( );
	return EXIT_SUCCESS;
}
