/* postgre2.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
/* weitere Typen siehe server/catalog/pg_type.h */
#define INT 23
#define VARCHAR 1043

static void exit_nicely (PGconn * conn) {
	PQfinish (conn);
	exit (EXIT_FAILURE);
}

static void read_fields (PGresult * res) {
	int i;
	int n_fields = PQnfields (res);
	printf("\n");
	for (i = 0; i < n_fields; i++)
		printf ("%s %s, ", PQfname (res, i),(PQftype (res, i) == INT) ? "INT" : "VARCHAR");
	printf ("\n\n");
}

static void read_full (PGresult * res) {
	int i, j;
	int n_fields = PQnfields (res);
	int n_line = PQntuples (res);
	printf("\n");
	for (j = 0; j < n_line; j++) {
		for (i = 0; i < n_fields; i++)
			printf ("%-15s", PQgetvalue (res, j, i));
		printf ("\n");
	}
	printf("\n");
}

static void read_info (PGresult * res) {
	int i, size = 0;
	int n_fields = PQnfields (res);
	int n_line = PQntuples (res);
	printf ("Tabelle enthält %d Zeile %d Spalten\n",n_line, n_fields);
	printf ("Speichergröße der einzelnen Spalten\n");
	for (i = 0; i < n_fields; i++) {
		printf ("%10s : %d Byte ", PQfname (res, i),PQfsize (res, i));
		if(PQfsize(res, i) != -1 ) {
			size += PQfsize (res, i);
			printf("\n");
		} else
			printf("( == Ein String mit variabler Länge)\n");
	}
	printf ("Gesamtspeichergröße ist %d Bytes\n", size);
}

static PGresult *select_all (char *dbName, PGconn * conn) {
	char query[255] = { "SELECT * FROM " };
	PGresult *res;
	strcat (query, dbName);
	res = PQexec (conn, query);
	if (!res || PQresultStatus (res) != PGRES_TUPLES_OK) {
		fprintf (stderr, "Fehler beim Befehl SELECT\n");
		PQclear (res);
		exit_nicely (conn);
	}
	return res;
}

int main (void) {
	/*char *pghost = NULL, *pgport = NULL,  */
	/*    *pgoptions = NULL, *pgtty = NULL; */
	char *dbName;
	char buf[64];
	char db[255] = { "dbname=" };
	PGconn *conn;
	PGresult *res;
	int auswahl;

	printf ("Mit welcher Datenbank wollen Sie arbeiten?: ");
	scanf ("%s", buf);
	dbName = buf;
	strcat (db, buf);
	/* ... bitte ggf. anpassen */
	conn = PQconnectdb (db);
	if (PQstatus (conn) == CONNECTION_BAD) {
		fprintf (stderr, "Verbindung z. Datenbank '%s' verfehlt\n",dbName);
		fprintf (stderr, "%s", PQerrorMessage (conn));
		exit_nicely (conn);
	}
	else
		printf ("Mit PostgreSQL-Server verbunden ...\n");
	do {
		printf ("-1- Info zur Datenbank %s\n", dbName);
		printf ("-2- Alle Spaltennamen ausgeben\n");
		printf ("-3- Komplette Datenbank %s ausgeben\n", dbName);
		printf ("-4- Ende\n");
		printf ("Ihre Auswahl : ");
		scanf ("%d", &auswahl);
		switch (auswahl) {
			case 1:
				res = select_all (buf, conn);
				read_info (res);
				PQclear (res);
			break;
			case 2:
				res = select_all (buf, conn);
				read_fields (res);
				PQclear (res);
			break;
			case 3:
				res = select_all (buf, conn);
				read_full (res);
				PQclear (res);
			break;
			default:
			break;
		}
	} while (auswahl != 4);
	PQfinish (conn);
	return EXIT_SUCCESS;
}
