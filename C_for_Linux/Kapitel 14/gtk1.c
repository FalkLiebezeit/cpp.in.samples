/* gkt1.c */
/* Ein leeres Fenster und Pixbuf */
#include <gtk/gtk.h>

static gint delete_Event(GtkWidget * widget, GdkEvent event, gpointer daten){
	g_print ("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}

static void end (GtkWidget * widget, gpointer daten) {
	g_print ("Und tschuess!\n");
	/* Die Verarbeitungsschleife beenden */
	gtk_main_quit ();
}

int main (int argc, char **argv) {
	GtkWindow *win;
	GdkPixbuf *pic;

	/* 1. Die Umgebung initialisieren */
	gtk_init (&argc, &argv);
	/* 2. Die Widgets erzeugen */
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file ("icon/at-work.gif", NULL);
	/* 2a. Fenster mit den folgenden Eigenschaften ... anlegen */
	win = g_object_new (GTK_TYPE_WINDOW,
	"title", "Ein leeres Fenster",
	"default-width", 300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 5, "icon", pic, NULL);

	/* 3. Signalhandler (Callback-Funktion) einrichten  */
	g_signal_connect ( win, "delete-event",G_CALLBACK (delete_Event), NULL);
	g_signal_connect ( win, "destroy",G_CALLBACK (end), NULL);
	/* 4. Hier gibt es noch nichts zum Packen */
	/* 5. (Widgets-)Fenster anzeigen */
	gtk_widget_show_all (GTK_WIDGET (win));
	/* 6. Hauptschleife von gtk-Verarbeitungsschleife */
	gtk_main ();
	g_print ("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
