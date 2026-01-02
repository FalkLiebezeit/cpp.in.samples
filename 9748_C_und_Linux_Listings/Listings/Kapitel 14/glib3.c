/* glib3.c */
#include <gtk/gtk.h>
#define MMAX 100

int main(void) {
	gpointer *mem, *dup;
	gchar *text = "Text zum Kopieren";

	/* Speicher reservieren */
	mem = g_malloc(MMAX);
	/* etwas in Speicher schreiben */
	g_snprintf((gchar *)mem, MMAX, "%s\n",text);
	/* Inhalt des Speichers ausgeben */
	g_print("mem: %s",(gchar *)mem);

	/* Speicherplatz duplizieren */
	dup = g_memdup(mem, MMAX);
	/* Inhalt des kopierten Speichers ausgeben */
	g_print("dup: %s",(gchar *)dup);
	/* kopierten Speicherplatz freigeben */
	g_free(dup);
	/* ein Fehler mit Absicht - Programmabbruch */
	mem = g_malloc( -1 );
	return 0;
}

