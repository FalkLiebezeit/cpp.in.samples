/* gkt2.c */
/* Anzeigeelemente:             */
/*       Label,                 */
/*       Grafik                 */
/*       Statusbar              */
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

int main(int argc, char *argv[]) {
	GtkWindow  *win;
	GdkPixbuf  *pic;
	GtkVBox    *vbox;
	GtkLabel   *text;
	GtkImage   *image;
	GtkStatusbar *bar;
	GtkHSeparator *sep1, *sep2, *sep3;

	gtk_init( &argc, &argv );
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new( GTK_TYPE_WINDOW,
	"title", "Verschiedene Anzeigeelemente",
	"default-width", 300,
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
	text = g_object_new(GTK_TYPE_LABEL,
	"label","Ein einfaches GtkLabel, das"
	" die\nAbbildung etwas beschreiben"
	" koennte.\n",
	"justify", GTK_JUSTIFY_FILL,
	NULL);
	/* 3 horizontale Separatoren (Linien) erzeugen */
	sep1 = g_object_new( GTK_TYPE_HSEPARATOR, NULL);
	sep2 = g_object_new( GTK_TYPE_HSEPARATOR, NULL);
	sep3 = g_object_new( GTK_TYPE_HSEPARATOR, NULL);
	/* Ein "Bild"-Widget erzeugen */
	image = g_object_new( GTK_TYPE_IMAGE,
	"file", "icon/john.png",
	NULL);
	/* Eine Statusbar erzeugen */
	bar = g_object_new( GTK_TYPE_STATUSBAR, NULL );
	/* Text in der Statusbar einf�gen */
	gtk_statusbar_push (bar, 0 ,
	"Informationen der aktellen Aktionen in der Statusbar");
	/* Gr��e der Statusbar nicht (FALSE) ver�nderbar */
	gtk_statusbar_set_has_resize_grip (bar, FALSE);

	/* Signalhandler einrichten */
	g_signal_connect( win, "delete-event",G_CALLBACK(delete_Event), NULL );
	g_signal_connect( win, "destroy",G_CALLBACK(end), NULL );

	/* Packen */
	/* vertikale Box in das Hauptfenster */
	gtk_container_add( GTK_CONTAINER(win), GTK_WIDGET(vbox));
	/* Einzelne Widgets von oben nach unten in die vertikale */
	/* Box packen                                            */
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(sep1));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(text));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(sep2));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(image));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(sep3));
	gtk_box_pack_start_defaults(GTK_BOX(vbox), GTK_WIDGET(bar));
	/* Fenster anzeigen */
	gtk_widget_show_all( GTK_WIDGET(win) );
	/* Hauptschleife von gtk */
	gtk_main();
	g_print("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
