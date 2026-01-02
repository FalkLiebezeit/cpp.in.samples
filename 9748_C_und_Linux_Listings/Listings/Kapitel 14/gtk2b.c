/* gkt2b.c */
/* Anzeigeelemente:             */
/*       Label mit Pango-Markup */
#include <gtk/gtk.h>

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
	GtkVBox    *vbox;
	GtkLabel   *text;

	gtk_init( &argc, &argv );
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new( GTK_TYPE_WINDOW,
	"title", "Demonstriert Pango-Markup",
	"default-width",  300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 5,
	"icon", pic,
	NULL );
	/* Eine vertikale Box erzeugen */
	vbox = g_object_new( GTK_TYPE_VBOX,
	"spacing", 5,
	"homogeneous", FALSE,
	NULL );

	/* Ein Text-Label erzeugen */
	text = g_object_new( GTK_TYPE_LABEL,
	"justify", GTK_JUSTIFY_CENTER,
	"use-markup", TRUE,
	"label",
	"<span font_desc=\"Times Normal 12\"> Times Normal 12</span> - "
	"<span font_desc=\"Verdana\"> Verdana </span> - "
	"<span font_desc=\"Courier Bold 10\"> Courier Bold 10 "
	" </span>\n\n"
	"<span style=\"italic\"> Kursiv </span> - "
	"<span style=\"oblique\"> Geschraegt </span> - "
	"<span style=\"normal\"> Normal </span>\n\n"
	"<span font_desc=\"Times Normal 12\"  background=\"white\""
	" foreground=\"blue\"> Invers1 </span> - "
 	"<span font_desc=\"Courier Bold 14\"  background=\"black\""
	" foreground=\"green\"> Invers2 </span> - "
	"<span style=\"italic\"  background=\"red\""
	" foreground=\"yellow\"> Invers3 </span>\n",
	NULL);

	/* Signalhandler einrichten */
	g_signal_connect( win, "delete-event",G_CALLBACK(delete_Event), NULL );
	g_signal_connect( win, "destroy",G_CALLBACK(end), NULL );
	/* Packen */
	gtk_container_add( GTK_CONTAINER(win), GTK_WIDGET(vbox));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(text));
	/* Fenster anzeigen */
	gtk_widget_show_all( GTK_WIDGET(win) );
	/* Hauptschleife von gtk */
	gtk_main();
	g_print("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
