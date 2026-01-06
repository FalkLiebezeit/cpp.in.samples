/* login.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#define MAX 255
#define BUFFER 4096
#include "my_cgi.h"

static char *connect_param[4];
/* Mit dem MySQL-Server und den entsprechenden */
/* Verbindungsdaten eine Verbindung herstellen  */
static int mein_connect (MYSQL * my, struct CGI_DATEN *ptr) {
	int i;
	for( i = 0; i < 4; i++ ) {
		connect_param[i] = ptr->wert;
		ptr = ptr->next;
	}
	/* Mit dem Server verbinden */
	if (mysql_real_connect (my,   /* Zeiger auf MySQL-Handler */
	connect_param[0],  /* Hostname */
	connect_param[1],  /* User-Name */
	connect_param[2],  /* Passwort für user_name */
	connect_param[3],  /* Name der Datenbank */
	0,  /* Port (default=0) */
	NULL, /* Socket (default=NULL) */
	0 /* keine Flags */ ) ==    NULL) {
		fprintf (stdout, "Fehler mysql_real_connect():""%u (%s)\n", mysql_errno (my), mysql_error (my));
		exit (EXIT_FAILURE);
	}
	return 1;
}

/* Speicher freigeben und Verbindung beenden */
static void clean_up_shutdown (MYSQL * my) {
	mysql_close (my);
}

int main (int argc, char **argv) {
	MYSQL *my;
	char *str;
	struct CGI_DATEN *cgi;
	struct CGI_DATEN *free_cgi;
	char buf[BUFFER];
	/* Handle initialisieren */
	my = mysql_init (NULL);
	if (my == NULL) {
		fprintf (stderr, " Initialisierung fehlgeschlagen\n");
		exit (EXIT_FAILURE);
	}
	 /* Für Fehlermeldungen */
	printf("Content-Type: text/html\n\n");
	 /* Eingabe einlesen */
	str = getdata();
	if(str == NULL) {
		printf("Fehler beim Einlesen der Formulareingabe");
		return 0;
	}
	/* Hexzeichen in ASCII-Zeichen konvertieren und aus '+'
   	Leerzeichen machen */
	hex2ascii(str);
	/* Liste der Formulardaten erstellen */
	cgi = erstellen(str);
	free_cgi = cgi;
	if (cgi == NULL) {
		printf("Fehler beim Erstellen der ""Variablen/Werteliste!!\n");
		return EXIT_FAILURE;
	}

	/* Mit dem Server verbinden */
	if (mein_connect (my, cgi) != -1)
		printf ("Erfolgreich mit dem MySQL-Server verbunden\n");
	/* Wenn alles o.k. ging, auf zum Admin-Bereich mit */
	/* den DB-Daten                                 */
	sprintf(buf,
	"<form action=\"http://localhost/cgi-bin/admin\""
	" method=\"POST\"><input type=\"hidden\"  name=\"host\""
	" value=\"%s\"><input type=\"hidden\"  name=\"user\"  "
	"value=\"%s\"><input type=\"hidden\"  name=\"passwort\"  "
	"value=\"%s\"><input type=\"hidden\"  name=\"datenbank\"  "
	"value=\"%s\">Login zur Datenbank erfolgreich. Zum"
	" Admin-Bereich auf den Button klicken.<br><input "
	"type=\"submit\"  value=\"Los gehts!\"></form>",
	connect_param[0], connect_param[1], connect_param[2],connect_param[3]);
	printf("%s\n",buf);
	clean_up_shutdown( my );
	return EXIT_SUCCESS;
}
