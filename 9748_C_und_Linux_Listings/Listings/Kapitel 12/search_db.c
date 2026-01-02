/* search_db.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#define MAX 255
#define BUFFER 4096
#include "my_cgi.h"
#define HOST      "localhost"
#define USER      "root"
#define PASSWORT  "k4p6m3o3"
#define DATENBANK "news"

static char *search_string;
static char *news_full;
static char *timestamp2date( char * );
static char date[11];

static int fetch_http_string (void) {
	char *str;
	struct CGI_DATEN *cgi;
	/* Eingabe einlesen */
	str = getdata ();
	if (str == NULL) {
		printf ("Fehler beim Einlesen von der Formulareingabe");
		return 0;
	}
	/* Hexzeichen in ASCII-Zeichen konvertieren und aus '+' */
	/* Leerzeichen machen                                   */
	hex2ascii (str);
	/* Liste der Formulardaten erstellen */
	cgi = erstellen (str);
	if (cgi == NULL) {
		printf ("Fehler beim Erstellen der ""Variablen/Werteliste!!\n");
		return 0;
	}
	/* Suche nur mit einem Suchbegriff möglich */
	news_full = cgi->variable;
	search_string = cgi->wert;
	return 1;
}

/* Mit dem MySQL-Server und den entsprechenden */
/* Verbindungsdaten eine Verbindung herstellen  */
static int mein_connect (MYSQL * my) {
	/* Mit dem Server verbinden */
	if (mysql_real_connect (my,   /* Zeiger auf MYSQL-Handler */
		HOST,      /* Hostname */
		USER,      /* User-Name */
		PASSWORT,  /* Passwort für user_name */
		DATENBANK, /* Name der Datenbank */
		0,       /* Port (default=0) */
		NULL,    /* Socket (default=NULL) */
		0 /* keine Flags */ ) == NULL) {
		fprintf (stdout, "Fehler mysql_real_connect():""%u (%s)\n", mysql_errno (my), mysql_error (my));
		exit (EXIT_FAILURE);
	}
	return 1;
}

/* Mit Suche integrieren */
static void
search_data_from_db (MYSQL * my) {
	char *tmp[6];
	MYSQL_ROW row;
	MYSQL_RES *mysql_res;
	unsigned long anzahl_reihen;
	unsigned int i;
	char buf[BUF];
	char bigbuf[8096];

	if (strcmp (news_full, "full") == 0) {
		sprintf ( buf,"SELECT * FROM data WHERE title=\'%s\';",search_string );
		/* printf ("%s", buf); */
		if (mysql_real_query (my, buf, strlen(buf)) != 0) {
			fprintf (stdout, "Fehler mysql_real_connect():"
			"%u (%s)\n", mysql_errno (my),
			mysql_error (my));
			exit (EXIT_FAILURE);
		}
		/* Daten der Anfrage abholen */
		mysql_res = mysql_store_result (my);
		printf ("<table width=\"90%\">");
		/* Gefundenen Datensatz bzw. Datensätze ausgeben */
       		while ((row = mysql_fetch_row (mysql_res)) != NULL) {
			/* Einzelne Spalten der Zeile ausgeben */
			for (i = 0; i < mysql_num_fields (mysql_res); i++)
				tmp[i] = row[i];
			sprintf (bigbuf,
			"<tr><td bgcolor=\"darkgrey\">Titel: %s</td></tr>"
			"<tr><td>Schlagzeile :%s<br><br>Inhalt: %s</td></tr>"
			"<tr><td bgcolor=\"darkgrey\"  align=\"right\">"
			" Datum :%s |  Autor :%s  |"
			"</td></tr><td><tr>&nbsp;</tr></td>",
			tmp[3], tmp[4],tmp[5], timestamp2date(tmp[0]), tmp[1]);
			printf ("%s", bigbuf);
		}
		printf ("</table>");
		printf ("<hr><br>"
		"<form action=\"http://localhost/cgi-bin/search_db\""
		" method=\"POST\">" "Nach Artikel suchen <br>"
		"<input type=\"text\"  maxlength=\"30\"name=\"suchstring\">"
		"<input type=\"submit\"  value=\"Suche\"></form>");
	} else {
		sprintf (buf,
		"SELECT * FROM data WHERE suche LIKE \'%%%s%%\'"
		" ORDER BY datum DESC;", search_string);
		/* printf ("%s", buf); */
		if (mysql_real_query (my, buf, strlen(buf)) != 0) {
			fprintf (stdout, "Fehler mysql_real_connect():"
			"%u (%s)\n", mysql_errno (my),
			mysql_error (my));
			exit (EXIT_FAILURE);
		}
		/* Daten der Anfrage abholen */
		mysql_res = mysql_store_result (my);
		/* Anzahl der gefundenen Datensätze ermitteln */
		anzahl_reihen = (unsigned long) mysql_num_rows (mysql_res);
		printf ("Anzahl gefundener Artikel: %lu\n\n<br><br>",anzahl_reihen);
		printf ("<table width=\"90%\">");
		/* Gefundenen Datensatz bzw. Datensätze ausgeben */
		while ((row = mysql_fetch_row (mysql_res)) != NULL) {
			/* Einzelne Spalten der Zeile ausgeben */
			for (i = 0; i < mysql_num_fields (mysql_res); i++)
				tmp[i] = row[i];
			sprintf (bigbuf,
			"<tr><td bgcolor=\"darkgrey\">Titel: %s</td>"
			"</tr><tr><td>Schlagzeile :%s</td></tr>"
			"<tr><td bgcolor=\"darkgrey\"  align=\"right\">"
			"Datum :%s |  Autor :%s  |  <a href=\""
			"http://localhost/cgi-bin/search_db?full=%s\">"
			"Den kompletten Artikel lesen</a>  |"
			"</td></tr><td><tr>&nbsp;</tr></td>",
			tmp[3], tmp[4], timestamp2date(tmp[0]),
			tmp[1], tmp[3]);
			printf ("%s", bigbuf);
		}
		printf ("</table>");
		printf ("<hr><br><form action=\""
		"http://localhost/cgi-bin/search_db\"  method=\"POST\">"
		"Nach Artikel suchen <br><input type=\"text\""
		" maxlength=\"30\"name=\"suchstring\">"
	        "<input type=\"submit\"  value=\"Suche\"></form>");
	}
	/* Speicherplatz wieder freigeben */
	mysql_free_result (mysql_res);
}

/* Extrahieren des Timestamp-Formats            */
/* bspw. 200404121602... das Datum              */
/* und gibt einen String à la DD:MM:YYYY zurück */
static char *timestamp2date( char *timestamp ) {
	char *ptr = NULL;
	date[0] = '\0';
	ptr = timestamp+6;
	strncpy(date, ptr, 2);
	strcat(date, ".");
	ptr = timestamp+4;
	strncpy(&date[3], ptr, 2);
	strcat(date, ".");
	ptr = timestamp;
	strncpy(&date[6], ptr, 4);
	date[10] = '\0';
	ptr = date;
	return ptr;
}

/* Speicher freigeben und Verbindung beenden */
static void
clean_up_shutdown (MYSQL * my) {
    mysql_close (my);
}

void print_header () {
	printf ( "<html><head><title>News</title></head>"
	"<body bgcolor=\"white\">" "<h1>News</h1>");
}

static void print_footer (void) {
	printf ("</body></html>");
}

int main (int argc, char **argv) {
	MYSQL *my;
	/* Handle initialisieren */
	my = mysql_init (NULL);
	if (my == NULL) {
		fprintf (stderr, " Initialisierung fehlgeschlagen\n");
		exit (EXIT_FAILURE);
	}
	/* Für Fehlermeldungen */
	printf ("Content-Type: text/html\n\n");
	/* Mit dem Server verbinden */
	if (mein_connect (my) != -1)
	print_header ();

	/* Suchstring auslesen */
	fetch_http_string ();
	/* Daten aus der Datenbank holen */
	search_data_from_db (my);
	print_footer ();
	clean_up_shutdown (my);
	return EXIT_SUCCESS;
}
