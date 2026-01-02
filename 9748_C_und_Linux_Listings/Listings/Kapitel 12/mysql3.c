/* mysql3.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#define MAX 255

/* Verbindungsdaten für mysql_real_connect */
static char *connect_param[7];
/* globaler Hilfszähler für die Verbindungsdaten */
static int connect_param_count = 0;

/*
*  Übernehmen Sie die my_fgets()-, my_cat()-, get_connect_param()-,
*  mein_connect()-, cleanup_shutdown()-Funktionen von oben.
*/

int main (int argc, char **argv) {
	MYSQL *my;
	int auswahl;

	/* Handle initialisieren */
	my = mysql_init (NULL);
	if (my == NULL) {
		fprintf (stderr, " Initialisierung fehlgeschlagen\n");
		exit (EXIT_FAILURE);
	}
	/* Verbindungsdaten für die Datenbank abfragen */
	get_connect_param ();
	/* Mit mit dem Server verbinden */
	if (mein_connect (my) != –1)
		printf ("Erfolgreich mit dem MySQL-Server verbunden\n");
		do {
			printf ("Informationen zum MySQL-Server auf"
				" Ihrem System\n");
			printf ("-----------------------------------"
				"------------\n\n");
			printf ("- 1 – Aktiven Zeichensatz ausgeben \n");
			printf ("- 2 – Versionsnummer des Clients\n");
			printf ("- 3 – Hostinformationen\n");
			printf ("- 4 – Protokollversion\n");
			printf ("- 5 – Versionsnummer des Servers\n");
			printf ("- 6 – Infos über die letzten MySQL-Abfragen\n");
			printf ("- 0 – Beenden\n\n");
			printf ("Ihre Auswahl : ");
			scanf ("%d", &auswahl);
			switch (auswahl) {
				case 1:
					printf ("\nZeichensatz auf Ihrem MySQL-System:  : %s\n\n",
						mysql_character_set_name (my));
					getchar ();
				break;
				case 2:
					printf ("\nVersionsnummer : %s\n\n",
						mysql_get_client_info ());
					getchar ();
				break;
				case 3:
					printf ("\nInfos zum Host : %s\n\n",
						mysql_get_host_info (my));

					getchar ();
				break;
				case 4:
					printf ("\nProtokollversion : %d\n\n",
						mysql_get_proto_info (my));
					getchar ();
				break;
				case 5:
					printf ("\nVersionsnummer : %s\n\n",
						mysql_get_server_info (my));
					getchar ();
				break;
				case 6:
					printf ("\nDie letzten Aktionen : %s\n\n",
						mysql_info (my));
					getchar ();
				break;
				case 0:
					printf ("Bye\n");
				break;
				default:
					printf ("Fehlerhafte Eingabe\n");
		}
	} while (auswahl != 0);
	/* Verbindung trennen */
	clean_up_shutdown (my);
	return EXIT_SUCCESS;
}
Listing 1.3: Gibt einige Informationen zur Datenbank und zur verwendeten MySQL-Version aus.
1.5.6	Datenbanken, Tabellen und Felder ausgeben mit MYSQL_RES
