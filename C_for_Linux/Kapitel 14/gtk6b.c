/* gkt6b.c */
/*        Optionsmenü     */
/*        Combo-Boxen     */
#include <gtk/gtk.h>

static GtkOptionMenu *options_menu;
static GtkCombo *combo;

static gchar *linux_t[] = {
	"SuSE Linux", "RedHat Linux", "Mandrake Linux",
	"Debian (Bullseye) Linux", "Geentoo Linux"
 };

static gint delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
	g_print ("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}
static void end (GtkWidget * widget, gpointer daten) {
	g_print ("Und tschuess!\n");
	gtk_main_quit ();
}

/* Auswerten des Optionsmenüs und der Combo-Box */
static void auswerten (GtkWidget * widget, gpointer daten) {
	gint i = gtk_option_menu_get_history (options_menu);
	gchar *opt;

	if (i == -1)
		g_print ("Fehler beim Auswerten der Combo-Box\n");
	else
		g_print ("Auswertung Combo-Box: %s\n", linux_t[i]);
	g_object_get (GTK_COMBO (combo)->entry, "text", &opt, NULL);
	g_print ("Auswerten Optionsmenue : %s\n", opt);
	g_print ("------------------------------------\n");
}

int main (int argc, char **argv) {
	GtkWindow *win;
	GdkPixbuf *pic;
	GtkTable *table;
	GtkMenu *menu;
	GList *combo_list = NULL;
	GtkButton *button;
	GtkLabel *option_label, *combo_label;
	gint i;

	gtk_init (&argc, &argv);
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file ("icon/at-work.gif", NULL);
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new (GTK_TYPE_WINDOW,
	"title", "Optionsmenues und Combo-Boxen",
	"default-width", 300,
	"default-height", 150,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 10, "icon", pic, NULL);
	/* Eine Tabelle 3x2 erzeugen */
	table = g_object_new (GTK_TYPE_TABLE,
	"n-rows", 3,
	"n-columns", 2,
	"row-spacing", 3,
	"column_spacing", 3,
	"homogeneous", FALSE, NULL);
	/* Ein neues Menü erzeugen */
	menu = g_object_new (GTK_TYPE_MENU, NULL);
	/* Menü mit Einträgen befüllen */
	for (i = 0; i < 5; i++)
		gtk_menu_shell_append (
		GTK_MENU_SHELL (menu),
		gtk_menu_item_new_with_label (linux_t[i]));
	/* Ein Optionsmenü erzeugen und mit dem Menü bestücken */
	options_menu = gtk_object_new ( GTK_TYPE_OPTION_MENU,
	"menu", menu,
	NULL);
	/* Ein Textfeld erzeugen */
	option_label = g_object_new ( GTK_TYPE_LABEL,
	"label", "Optionsmenue ",
	NULL );
	/* Eine neue Combo-Box erzeugen */
	combo = g_object_new (GTK_TYPE_COMBO, NULL);
	/* Einräge zu Combo-Box hinzufügen */
	for (i = 0; i < 5; i++)
		combo_list = g_list_append (combo_list, linux_t[i]);
	/* Liste von Einträgen an Combo-Box übergeben */
	gtk_combo_set_popdown_strings (GTK_COMBO (combo), combo_list);
	/* Liste kann wieder freigegeben werden, da */
	/* nicht mehr benötigt */
	g_list_free (combo_list);
	/* Ein neues Label erzeugen */
	combo_label = g_object_new ( GTK_TYPE_LABEL,
	"label", "Combo-Box ",
	NULL);
	/* Einen neuen Button erzeugen */
	button = g_object_new ( GTK_TYPE_BUTTON,
	"label", "Auswerten",
	"relief", GTK_RELIEF_HALF,
	NULL);
	/* Signalhandler einrichten */
	g_signal_connect ( win, "delete-event",G_CALLBACK (delete_Event), NULL);
	g_signal_connect ( win, "destroy",G_CALLBACK (end), NULL );
	g_signal_connect ( button, "clicked",G_CALLBACK (auswerten), NULL );
	/* Alles packen */
	gtk_container_add (GTK_CONTAINER (win), GTK_WIDGET (table));
	gtk_table_attach(GTK_TABLE (table), GTK_WIDGET (option_label),
	0, 1, 0, 1,
	GTK_FILL, GTK_FILL,
	10, 0);
	gtk_table_attach(GTK_TABLE (table), GTK_WIDGET (options_menu),
	1, 2, 0, 1,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach (GTK_TABLE (table), GTK_WIDGET (combo_label),
	0, 1, 1, 2,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach (GTK_TABLE (table), GTK_WIDGET (combo),
	1, 2, 1, 2,
	GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach (GTK_TABLE (table), GTK_WIDGET (button),
	1, 2, 2, 3,
	GTK_FILL, GTK_FILL, 0, 20);
	/* Fenster anzeigen */
	gtk_widget_show_all (GTK_WIDGET (win));
	/* Hauptschleife von gtk */
	gtk_main ();
	g_print ("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
