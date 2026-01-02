/* gkt5.c */
/* Dateneingabe: */
/*    Textfelder - GtkEntry          */
/*    Schieberegler -  GtkScale      */
/*    Zahlenfelder  -  GtkSpinButton */
#include <gtk/gtk.h>
#define VBOX   3
#define ENTRYS 3
#define SCALES 3
#define SPIN   2
#define BUF 50

static  GtkEntry   *entry[ENTRYS];
static  GtkVScale  *vscale[SCALES];
static  GtkAdjustment *vadj[SCALES];
static  GtkSpinButton  *spin[SPIN];
static  GtkAdjustment *spinadj[SPIN];

static gint
delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
	g_print("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}

static void end ( GtkWidget *widget, gpointer daten ) {
	g_print("Und tschuess!\n");
	gtk_main_quit();
}

/* Auswertung Eingabefelder */
static void entry_auswerten(gpointer auswert) {
	gchar *e1, *e2, *e3;
	g_object_get(entry[0], "text", &e1, NULL);
	g_object_get(entry[1], "text", &e2, NULL);
	g_object_get(entry[2], "text", &e3, NULL);
	g_print("Entry-Feld Auswertung:\n");
	g_print("Name, Vorname    : %s\n", e1);
	g_print("Strasse, Hausnr. : %s\n", e2);
	g_print("Ort, PLZ         : %s\n", e3);
	g_print("---------------------------\n");
}

/* Auswertung Schieberegler */
static void scale_auswerten(GtkAdjustment *adj, gpointer scale) {
	g_print("Schieberegler Auswertung:\n");
	g_print("Regler 1 : %.1f\n",
		gtk_adjustment_get_value(vadj[0]));
	g_print("Regler 2 : %.1f\n",
		gtk_adjustment_get_value(vadj[1]));
	g_print("Regler 3 : %.1f\n",
		gtk_adjustment_get_value(vadj[2]));
}

/* Auswertung Zahlenfelder */
static void spin_auswerten(GtkAdjustment *adj, gpointer scale) {
	g_print("Zahlenfelder Auswertung:\n");
	g_print("Regler 1 : %.1f\n",
		gtk_adjustment_get_value(spinadj[0]));
	g_print("Regler 2 : %.1f\n",
		gtk_adjustment_get_value(spinadj[1]));
}

/* Eingabefelder zurücksetzen - löschen */
static void entry_loeschen(gpointer auswert) {
	gint i;
	for(i=0; i<ENTRYS; i++)
		gtk_entry_set_text(entry[i], "");
}

int main(int argc, char **argv) {
	GtkWindow  *win;
	GdkPixbuf  *pic;
	GtkTable   *table;
	GtkLabel   *label[ENTRYS];
	GtkButton  *entry_button[2];
	GtkHBox    *hbox, *hbox_2, *hbox_vscale;
	GtkVBox    *vbox, *vbox_spin;
	GtkHSeparator *hsep;
	guint i;

	gtk_init( &argc, &argv );
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new( GTK_TYPE_WINDOW,
	"title", "Dateieingabe",
	"default-width",  380,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 10,
	"icon", pic,
	NULL );
	/* Eine Tabelle 8x3 erzeugen */
	table = g_object_new( GTK_TYPE_TABLE,
	"n-rows", 8,
	"n-columns", 3,
	"row-spacing", 3,
	"column-spacing" , 3,
	"homogeneous", FALSE,
	NULL);
	/* horizontale Box erzeugen */
	hbox = g_object_new( GTK_TYPE_HBOX,
	"spacing", 10,
	NULL );
	/* horizontale Box erzeugen */
	hbox_2 = g_object_new( GTK_TYPE_HBOX,
	"spacing", 10,
	NULL );
	/* horizontale Box für Schieberegler erzeugen */
	hbox_vscale = g_object_new( GTK_TYPE_HBOX,
	"spacing", 20,
	NULL );
	/* vertikale Box erzeugen */
	vbox = g_object_new( GTK_TYPE_VBOX,
	"spacing", 10,
	NULL );
	/* vertikale Box für Zahlenfelder erzeugen */
	vbox_spin = g_object_new( GTK_TYPE_VBOX,
	"spacing", 7,
	NULL );
	/* ENTRYS Textfelder erzeugen */

	for(i=0; i < ENTRYS; i++)
		entry[i] = g_object_new( GTK_TYPE_ENTRY,
		"text", "Ihre Eingabe hier ...",
		"max-length"  ,BUF,
		NULL );
	/* Labels für die Textfelder erzeugen */
	label[0] = g_object_new( GTK_TYPE_LABEL,
	"justify", GTK_JUSTIFY_LEFT,
	"label", "Name, Vorname",
	NULL );
	label[1] = g_object_new( GTK_TYPE_LABEL,
	"label", "Strasse/Hausnr.",
	NULL );
	label[2] = g_object_new( GTK_TYPE_LABEL,
	"label", "Ort, Postleitz.",
	NULL );
	/* Buttons zum Auswerten der Textfelder erzeugen */
	entry_button[0] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Auslesen",
	NULL );
	entry_button[1] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Reset",
	NULL );
	/* SCALES Stellgrößen für die Schieberegler erzeugen */
	for(i=0; i<SCALES; i++)
		vadj[i] = GTK_ADJUSTMENT(
		gtk_adjustment_new(1.0,
		-100.0,
		100.0,
		0.1,
		10.0,
		0.0) );
	/* SCALES vertikale Schieberegler erzeugen */
	for(i=0; i<SCALES; i++)
		vscale[i] = g_object_new( GTK_TYPE_VSCALE,
		"adjustment", vadj[i],
		NULL );
	/* SPIN Stellgrößen für die Zahlenfelder erzeugen */
	for(i=0; i<SPIN; i++)
		spinadj[i] = GTK_ADJUSTMENT(
		gtk_adjustment_new(1.0,
		-100.0,
		100.0,
		0.1,
		10.0,
		0.0) );
	/* SPIN Zahlenfelder erzeugen */
	for(i=0; i<SPIN; i++)
		spin[i] = g_object_new( GTK_TYPE_SPIN_BUTTON,
		"adjustment", spinadj[i],
		"digits", 1,
		"value", 20.0,
		NULL );
	/* horizontale Linie erzeugen */
	hsep = g_object_new( GTK_TYPE_HSEPARATOR, NULL);
	/* Signalhandler einrichten */
	g_signal_connect( win, "delete-event",
		G_CALLBACK(delete_Event), NULL );
	g_signal_connect( win, "destroy",
		G_CALLBACK(end), NULL );
	/* Signalhandler für die Buttons */
	g_signal_connect( entry_button[0], "clicked",
		G_CALLBACK(entry_auswerten), NULL);
	g_signal_connect( entry_button[1], "clicked",
		G_CALLBACK(entry_loeschen), NULL);
	/* Signalhandler, wenn sich einer der */
	/* Schieberegler verändert */
	g_signal_connect( vscale[0], "value-changed",
		G_CALLBACK(scale_auswerten), NULL);
	g_signal_connect( vscale[1], "value-changed",
		G_CALLBACK(scale_auswerten), NULL);
	g_signal_connect( vscale[2], "value-changed",
		G_CALLBACK(scale_auswerten), NULL);
	/* Signalhandler, wenn sich eines der Zahlenfelder */
	/* verändert */
	g_signal_connect( spin[0], "value-changed",
		G_CALLBACK(spin_auswerten), NULL);
	g_signal_connect( spin[1], "value-changed",
		G_CALLBACK(spin_auswerten), NULL);
	/* Großes Packen der Widget beginnt */
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(label[0]),
	0, 1, 0, 1,
	GTK_FILL, GTK_FILL, 0, 0 );
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(entry[0]),
	1, 2, 0, 1,
	GTK_FILL, GTK_FILL, 0, 0 );
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(label[1]),
	0, 1, 2, 3,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(entry[1]),
	1, 2, 2, 3,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(label[2]),
	0, 1, 4, 5,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(entry[2]),
	1, 2, 4, 5,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(hbox),
	1, 2, 6, 7,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_box_pack_start_defaults( GTK_BOX(hbox),
	GTK_WIDGET(entry_button[0]) );
	gtk_box_pack_start_defaults( GTK_BOX(hbox),
	GTK_WIDGET(entry_button[1]) );
	gtk_box_pack_start_defaults( GTK_BOX(vbox_spin),
	GTK_WIDGET(hsep) );
	gtk_box_pack_start_defaults( GTK_BOX(vbox_spin),
	GTK_WIDGET(spin[0]) );
	gtk_box_pack_start_defaults( GTK_BOX(vbox_spin),
	GTK_WIDGET(spin[1]) );
	gtk_table_attach ( GTK_TABLE (table), GTK_WIDGET(vbox_spin),
                     1, 2, 7, 8,
                     GTK_FILL, GTK_FILL, 0, 0);
	for(i=0; i<SCALES; i++)
		gtk_box_pack_start_defaults( GTK_BOX(hbox_vscale),
		GTK_WIDGET(vscale[i]) );
	gtk_container_add( GTK_CONTAINER( vbox ),
	GTK_WIDGET( hbox_2) );
	gtk_container_add( GTK_CONTAINER( hbox_2 ),
	GTK_WIDGET( table ) );
	gtk_container_add( GTK_CONTAINER( hbox_2 ),
	GTK_WIDGET( hbox_vscale ) );
	gtk_container_add( GTK_CONTAINER( win ), GTK_WIDGET( vbox ) );
	/* Fenster anzeigen */
	gtk_widget_show_all( GTK_WIDGET(win) );
	/* Hauptschleife von gtk */
	gtk_main();
	g_print("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
