/* mysql1.c */
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

/* Bitte Daten anpassen. */
#define HOST     "localhost"
#define USER     "root"
#define PASSWORT "k4p6m3o3"
#define DBNAME   NULL
#define PORT     0
#define SOCKET   NULL
#define FLAG     0

int main (int argc, char **argv) {
	MYSQL *my;
	/* Handle initialisieren */
	my = mysql_init (NULL);
	if (my == NULL) {
		fprintf (stderr, " Initialisierung fehlgeschlagen\n");
		exit (EXIT_FAILURE);
	}
	/* Mit mit dem Server verbinden */
	if (mysql_real_connect (my,     /* Zeiger auf MySQL-Handler */
		HOST,     /* Hostname */
		USER,     /* User-Name */
		PASSWORT, /* Passwort für user_name */
		DBNAME,   /* Name der Datenbank */
		PORT,     /* Port (defaultDefault = 0) */
		SOCKET,   /* Socket (defaultDefault = NULL) */
		FLAG      /* keine Flags */
	) == NULL) {
		fprintf (stderr, "Fehler mysql_real_connect():"
			"%u (%s)\n", mysql_errno (my), mysql_error (my));
	}
	else
		printf ("Erfolgreich mit dem MySQL-Server verbunden\n");

	/* Hier befindet sich der Code für die Arbeit mit MySQL. */

	/* Verbindung trennen */
	mysql_close (my);
	return EXIT_SUCCESS;
}
Listing 1.1: zeigtZeigt, wie Sie eine Verbindung mit einem SQL-Server herstellen.
