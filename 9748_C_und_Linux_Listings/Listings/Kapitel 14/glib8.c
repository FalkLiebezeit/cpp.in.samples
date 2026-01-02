/* glib8.c */
#include <gtk/gtk.h>
#include <stdio.h>
#define MMAX 255

static struct daten {
	gchar ort[MMAX];
	guint plz;
};

static struct daten help;
static guint count = 0;

static void read_data (void) {
	g_print ("Ort eingeben          : ");
	fgets (help.ort, MMAX, stdin);
	g_strchomp (help.ort);
	g_print ("Postleitzahl eingeben  : ");
	scanf ("%d", &help.plz);
}

static void insert_beginn (GArray * arr) {
	read_data ();
	g_array_prepend_vals (arr, &help, 1);
	count++;
}

static void insert_end (GArray * arr) {
	read_data ();
	g_array_append_vals (arr, &help, 1);
	count++;
}

static void insert_middle (GArray * arr) {
	guint pos;
	read_data();
	g_print ("Position angeben: ");
	scanf ("%d", &pos);
	if (pos < count) {
		g_array_insert_vals (arr, pos, &help, 1);
		count++;
	}
	else
		g_print ("Konnte Array nicht einfuegen (%d < %d)\n",
		pos, count);
}

static void remove_array (GArray * arr) {
	guint pos;
	g_print ("Position zum Loeschen angeben : ");
	scanf ("%d", &pos);
	if (pos < count) {
		g_array_remove_index (arr, pos);
		count--;
	}
	else
	g_print ("Konnte Array nicht entfernen (%d < %d)\n",
		pos, count);
}

static void show_arrays (GArray * arr) {
	struct daten test;
	guint pos = 0;
	while (pos < count) {
		test = g_array_index (arr, struct daten, pos);
		g_print ("Ort:  %s\n", test.ort);
		g_print ("PLZ:  %d\n", test.plz);
		pos++;
	}
}

int main (int argc, char **argv) {
	GArray *darray;
	guint auswahl;

	darray = g_array_new (FALSE, FALSE, sizeof (struct daten));
	do {
		printf ("Demonstration: dynamische Arrays (GLib )\n\n");
		printf ("1 - Neue Daten am Anfang einfuegen\n");
		printf ("2 - Neue Daten am Ende einfuegen\n");
		printf ("3 - Neue Daten an gewuenschte Pos. einfuegen\n");
		printf ("4 - Daten entfernen\n");
		printf ("5 - Daten ausgeben\n");
		printf ("0 - Programmende\n");
		printf ("\nIhre Auswahl : ");
		scanf ("%d", &auswahl);
		getchar ();
		switch (auswahl) {
			case 1:
				insert_beginn (darray);
			break;
			case 2:
				insert_end (darray);
			break;
			case 3:
				insert_middle (darray);
			break;
			case 4:
				remove_array (darray);
			break;
			case 5:
				show_arrays (darray);
			break;
		}
	}
	while (auswahl != 0);
	g_array_free (darray, TRUE);
	return 0;
}

