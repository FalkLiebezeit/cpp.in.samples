/* gkt6.c */
/* Ein einfaches Menü    */
/*        GtkItemFactory */
/*        GtkToolbar     */
#include <gtk/gtk.h>

static gint
delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
	g_print ("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}

static void end (GtkWidget * widget, gpointer daten) {
	g_print ("Und tschuess!\n");
	gtk_main_quit ();
}

/* Auswahl der Menüs auswerten und die Auswahl     */
/* mit einer einfachen Dialogbox anzeigen lassen   */
static void menuitem_auswerten (gpointer callback_data, guint callback_action, GtkWidget * widget) {
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (
	GTK_WINDOW (callback_data),
	GTK_DIALOG_DESTROY_WITH_PARENT,
	GTK_MESSAGE_INFO,
	GTK_BUTTONS_CLOSE,
	"Ihre Menueauswahl war: \"%s\"",
	gtk_item_factory_path_from_widget
	(widget));
	/* Sobald Dialog bestätigt, auch wieder zerstören */
	g_signal_connect ( dialog, "response",G_CALLBACK (gtk_widget_destroy), NULL);
	/* Dialogbox anzeigen */
	gtk_widget_show (dialog);
}

/* Ein Toolbar-Element wurde betätigt ...               */
/* Gewöhnlich wird für jedes Toolbar-Element eine extra */
/* Callback-Funktion erstellt - Neu, Speichern, ...     */
/* ... daher hierzu nur ein einfaches Dialogfenster     */
static void
toolbar_auswerten (GtkWidget * button, gpointer data) {
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (
	GTK_WINDOW (data),
	GTK_DIALOG_DESTROY_WITH_PARENT,
	GTK_MESSAGE_INFO,
	GTK_BUTTONS_CLOSE,
	"Es wurde ein Toolbar-Button betaetigt");
	/* Sobald Dialog bestätigt, auch wieder zerstören */
	g_signal_connect ( dialog, "response",G_CALLBACK (gtk_widget_destroy), NULL);
	/* Dialogbox anzeigen */
	gtk_widget_show (dialog);
}

int main (int argc, char **argv) {
	GtkWindow *win;
	GdkPixbuf *pic;
	GtkVBox *vbox;
	GtkWidget *menu_bar;
	GtkAccelGroup *accel_group;
	GtkItemFactory *itemfac;
	GtkToolbar *toolbar;
	/* Die einzelnen Menüelemente */
	static GtkItemFactoryEntry menu[] = {
		{"/_Datei", NULL, 0, 0, "<Branch>"},
		{"/Datei/_Neu", "<control>N", menuitem_auswerten, 0,
			"<StockItem>", GTK_STOCK_NEW},
		{"/Datei/_Oeffnen", "<control>O", menuitem_auswerten, 0,
			"<StockItem>", GTK_STOCK_OPEN},
		{"/Datei/_Speichern", "<control>S", menuitem_auswerten, 0,
			"<StockItem>", GTK_STOCK_SAVE},
		{"/Datei/Speichern unter...", NULL, menuitem_auswerten, 0,
			"<StockItem>", GTK_STOCK_SAVE},
		{"/Datei/sep1",NULL, menuitem_auswerten, 0,"<Separator>"},
		{"/Datei/_Ende", "<control>E", end, 0, "<StockItem>",
			GTK_STOCK_QUIT},
		{"/_Eigenschaften", NULL, 0, 0, "<Branch>"},
		{"/_Eigenschaften/_Farbe", NULL, 0, 0, "<Branch>"},
		{"/_Eigenschaften/Farbe/_Rot", NULL, 0, 0, "<RadioItem>"},
		{"/_Eigenschaften/Farbe/_Gruen", NULL, 0, 0,
			"/Eigenschaften/Farbe/Rot"},
		{"/_Eigenschaften/Farbe/_Blau", NULL, 0, 0,
			"/Eigenschaften/Farbe/Rot"},
		{"/_Eigenschaften/_Form", NULL, 0, 0, "<Branch>"},
		{"/_Eigenschaften/Form/_Quadrat", NULL, 0, 0,
			"<RadioItem>"},
		{"/_Eigenschaften/Form/_Rechteck", NULL, 0, 0,
			"/Eigenschaften/Form/Quadrat"},
		{"/_Eigenschaften/Form/_Kreis", NULL, 0, 0,
			"/Eigenschaften/Form/Quadrat"},
		{"/_Hilfe", NULL, 0, 0, "<LastBranch>"},
		{"/Hilfe/_Ueber", NULL, menuitem_auswerten, 0},
	};

	gtk_init (&argc, &argv);
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file ("icon/at-work.gif", NULL);
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new (GTK_TYPE_WINDOW,
	"title", "Menue und Toolbar",
	"default-width", 300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 0, "icon", pic, NULL);
	/* vertikale Box erzeugen */
	vbox = g_object_new (GTK_TYPE_VBOX, "spacing", 0, NULL);
	/* Neue Gruppe von Tastaturkürzeln erzeugen */
	accel_group = g_object_new (GTK_TYPE_ACCEL_GROUP, NULL);
	/* Tastaturkürzel-Gruppe mit dem Hauptfenster verknüpfen */
	gtk_window_add_accel_group (win, accel_group);
	/* Ein neues Widget der Klasse GtkItemFactory erzeugen */
	itemfac = gtk_item_factory_new ( GTK_TYPE_MENU_BAR,
	"<main>", accel_group);

	/* Jetzt kann das Menü mit einem Rutsch mit seinen */
	/* Elementen bestückt werden                       */
	gtk_item_factory_create_items (itemfac,sizeof (menu) / sizeof (menu[0]), menu, NULL );
	/* Menüleiste zum späteren "Packen" abholen */
	menu_bar = gtk_item_factory_get_widget (itemfac, "<main>");
	/* Tastenkombination STRG+G für Radio-Menüauswahl 'Grün' */
	gtk_widget_add_accelerator (
		gtk_item_factory_get_widget (
		itemfac, "/Eigenschaften/Farbe/Gruen"),
		"activate", accel_group,
		'G', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	/* Kombination Shift+S für Auswahl 'Speichern unter ...' */
	gtk_widget_add_accelerator (
		gtk_item_factory_get_widget (
		itemfac, "/Datei/Speichern unter ..."),
		"activate", accel_group,
		'S', GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	/* Tastenkombination Shift+STRG+H für Menüauswahl 'Ueber' */
	gtk_widget_add_accelerator (
		gtk_item_factory_get_widget (
		itemfac, "/Hilfe/Ueber"),
		"activate", accel_group,
		'H', GDK_SHIFT_MASK|GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	/* Eine neue Toolbar erzeugen */
	toolbar = g_object_new (GTK_TYPE_TOOLBAR, NULL);
	/* Einzelne Buttons mit Icon, Beschriftung und  */
	/* Tooltipp einfügen                            */
	gtk_toolbar_insert_stock (
	GTK_TOOLBAR (toolbar),
	GTK_STOCK_NEW,
	"Ein Button mit einem 'NEU' Icon", NULL,
	G_CALLBACK (toolbar_auswerten), win, -1);

	gtk_toolbar_insert_stock (
	GTK_TOOLBAR (toolbar),
	GTK_STOCK_OPEN,
	"Ein Button mit einem 'Oeffnen'-Icon",
	NULL,
	G_CALLBACK (toolbar_auswerten), win, -1);
	gtk_toolbar_insert_stock (
	GTK_TOOLBAR (toolbar),
	GTK_STOCK_SAVE,
	"Ein Button mit einem 'SPEICHERN'-Icon",
	NULL,
	G_CALLBACK (toolbar_auswerten), win, -1);
	gtk_toolbar_insert_stock (
	GTK_TOOLBAR (toolbar),
	GTK_STOCK_QUIT,
	"Ein Button mit einem 'ENDE'-Icon",
	NULL, G_CALLBACK (end), win, -1);
	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar));
	gtk_toolbar_insert_stock (
	GTK_TOOLBAR (toolbar),
	GTK_STOCK_DIALOG_QUESTION,
	"Ein Button mit einem 'FRAGE'-Icon",
	NULL,
	G_CALLBACK (toolbar_auswerten), win, -1);

	/* Signalhandler einrichten */
	g_signal_connect ( win, "delete-event",G_CALLBACK (delete_Event), NULL );
	g_signal_connect ( win, "destroy",G_CALLBACK (end), NULL );
	/* Alles packen */
	gtk_container_add (GTK_CONTAINER (win), GTK_WIDGET (vbox));
	gtk_box_pack_start ( GTK_BOX (vbox), menu_bar,FALSE, FALSE, 0 );
	gtk_box_pack_start ( GTK_BOX (vbox), GTK_WIDGET (toolbar),FALSE, FALSE, 0);
	/* Fenster anzeigen */
	gtk_widget_show_all (GTK_WIDGET (win));
	/* Hauptschleife von gtk */
	gtk_main ();
	g_print ("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
