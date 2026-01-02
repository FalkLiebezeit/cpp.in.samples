/* glib1.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gtk/gtk.h>
int main(void) {
	FILE *f1;
	const gchar *text = "Ausgabe mit g_message";
	g_print("Ausgabe mit g_print\n");
	g_printerr("Ausgabe mit g_printerr\n");
	g_message("%s\n",text);
	g_warning("Ausgabe mit g_warning\n");
	f1 = fopen("abcd", "r");
	if( f1 == NULL ) {
		printf("Fehler : %s\n", g_strerror(errno));
	}
	g_error("Ausgabe mit g_error (FATALER FEHLER - Ende)\n");
	return EXIT_SUCCESS;
}
