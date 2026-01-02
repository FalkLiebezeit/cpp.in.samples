/* glib2.c */
#include <gtk/gtk.h>

static void myfunc( gint val1, gint val2 ) {
	g_return_if_fail( (val1 > 0 && val2 > 0) );
	/* Tu was ... */
	g_print("val1 und val2 haben nicht den Wert 0\n");
	return;
}

int main(void) {
	myfunc(5, 4);
	myfunc(3, 1);
	myfunc(0, 3); /* Fehler - aber nicht kritisch */
	g_print("Kein Programmabbruch!\n");
	return 0;
}

