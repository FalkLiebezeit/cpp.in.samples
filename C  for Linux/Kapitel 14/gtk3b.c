/* gtk3b.c */
/* Behälter:        */
/*    Tabellen-Demo */
#include <gtk/gtk.h>
#define BUTTONS 3

static gint delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
	g_print("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}

static void end ( GtkWidget *widget, gpointer daten ) {
	g_print("Und tschuess!\n");
	gtk_main_quit();
}

int main(int argc, char **argv) {
	GtkWindow  *win;
	GdkPixbuf  *pic;
	GtkTable   *table;
	GtkButton  *button1, *button2, *button3;

	gtk_init( &argc, &argv );
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new( GTK_TYPE_WINDOW,
	"title", "Eine einfache Tabelle",
	"default-width",  300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 10,
	"icon", pic,
	NULL );
	button1 = g_object_new( GTK_TYPE_BUTTON,
	"label","Kein Schrumpfen\nkein Expandieren",
	NULL);

	button2 = g_object_new( GTK_TYPE_BUTTON,
	"label","Expandiert und schrumpft\nvertikal",
	NULL);

	button3 = g_object_new( GTK_TYPE_BUTTON,
	"label","Expandiert und schrumpft\n in beide Seiten",
	NULL);
	table = g_object_new( GTK_TYPE_TABLE,
	"n-columns", 2,
	"n-rows", 2,
	NULL);
	/* Signalhandler einrichten */
	g_signal_connect( win, "delete-event",
		G_CALLBACK(delete_Event), NULL );
	g_signal_connect( win, "destroy",
		G_CALLBACK(end), NULL );

	/* Inhalt der Tabelle mit verschiedenen Optionen erstellen */
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(button1),
		0, 1, 0, 1,
		GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(button2),
		0, 1, 1, 2,
		GTK_FILL, GTK_FILL|GTK_EXPAND|GTK_SHRINK,
		0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(button3),
		1, 2, 1, 2,
		GTK_FILL | GTK_EXPAND | GTK_SHRINK,
		GTK_FILL | GTK_EXPAND | GTK_SHRINK, 0, 0);
	gtk_container_add(GTK_CONTAINER( win ), GTK_WIDGET( table ) );
	/* Fenster anzeigen */
	gtk_widget_show_all( GTK_WIDGET(win) );
	/* Hauptschleife von gtk */
	gtk_main();
	g_print("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
