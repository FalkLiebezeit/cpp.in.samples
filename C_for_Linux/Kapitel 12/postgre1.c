/* postgre1.c */
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void exit_nicely(PGconn *conn) {
	PQfinish(conn);
	exit(EXIT_FAILURE);
}

int main(void) {
	/* char    *pghost = NULL,
	 *         *pgport = NULL,
	 *         *pgoptions = NULL,
	 *         *pgtty = NULL; */
	char       *dbName = "adressen";
	PGconn     *conn;
	/* ... entsprechende Angaben selbst ergänzen - */
	/* Verbindungsaufbau                           */
	conn = PQconnectdb("dbname=adressen");
	/* Verbindung überprüfen ... */
	if (PQstatus(conn) == CONNECTION_BAD) {
		fprintf(stderr, "Connection to database '%s' failed.\n",dbName);
		fprintf(stderr, "%s", PQerrorMessage(conn));
		exit_nicely(conn);
	}
	else
		printf("Mit PostgreSQL-Server verbunden ...\n");
	/* Informationen zur Verbindung ... */
	printf("Datenbank : %s\n", PQdb(conn));
	printf("User      : %s\n", PQuser(conn));

	/*   printf("Passwort  : %s\n", PQpass(conn));
	 *   printf("Host      : %s\n", PQhost(conn));
	 *   printf("Port      : %s\n", PQport(conn));
	 *   printf("TTY       : %s\n", PQtty(conn));
	 *   printf("Options   : %s\n", PQoptions(conn)); */
	/* Verbindung beenden und Aufräumarbeiten durchführen */
	PQfinish(conn);
	return EXIT_SUCCESS;
}
