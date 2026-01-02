/* gkt4.c */
/* Buttons:        */
/*    Button-Demo */
#include <gtk/gtk.h>
#define VBOX 5
#define BUTTONS 4
#define LABEL   4
#define BUF 50

static GtkToggleButton *tbuttons[BUTTONS];
static GtkRadioButton  *rbuttons[BUTTONS];
static GtkCheckButton  *cbuttons[BUTTONS];

static gint delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
	g_print("Das Fenster wird zerstoert!\n");
	/* Nur mit FALSE wird die Anwendung wirklich beendet */
	return FALSE;
}

static void end ( GtkWidget *widget, gpointer daten ) {
	g_print("Und tschuess!\n");
	gtk_main_quit();
}

/* Zustand aller Umschaltbuttons auswerten */
static void toogled_auswerten(gpointer button) {
	gboolean toogled1, toogled2, toogled3, toogled4 = FALSE;

	g_print("Toogled-Button Auswertung:\n");
	g_object_get(tbuttons[0], "active", &toogled1, NULL);
	g_object_get(tbuttons[1], "active", &toogled2, NULL);
	g_object_get(tbuttons[2], "active", &toogled3, NULL);
	g_object_get(tbuttons[3], "active", &toogled4, NULL);
	if(toogled1)
		g_print("Toogled-Button 1 ist aktiviert\n");
	if(toogled2)
		g_print("Toogled-Button 2 ist aktiviert\n");
	if(toogled3)
		g_print("Toogled-Button 3 ist aktiviert\n");
	if(toogled4)
		g_print("Toogled-Button 4 ist aktiviert\n");
	if(!toogled1 && !toogled2 && !toogled3 && !toogled4)
		g_print("Kein Toogled-Button ist aktiv\n");
	g_print("--------------------------------\n");
}

/* Zustand aller Radio-Buttons auswerten */
static void radio_auswerten(gpointer button) {
	gboolean radio1, radio2, radio3, radio4 = FALSE;

	g_print("Radio-Button Auswertung:\n");
	g_object_get(rbuttons[0], "active", &radio1, NULL);
	g_object_get(rbuttons[1], "active", &radio2, NULL);
	g_object_get(rbuttons[2], "active", &radio3, NULL);
	g_object_get(rbuttons[3], "active", &radio4, NULL);
	if(radio1)
		g_print("Radio-Button 1 ist aktiviert\n");
	else if(radio2)
		g_print("Radio-Button 2 ist aktiviert\n");
	else if(radio3)
		g_print("Radio-Button 3 ist aktiviert\n");
	else
		g_print("Radio-Button 4 ist aktiviert\n");
	g_print("--------------------------------\n");
}

/* Zustand aller Ankreuz-Buttons auswerten */
static void check_auswerten(gpointer button) {
	gboolean check1, check2, check3, check4 = FALSE;

	g_print("Check-Button Auswertung:\n");
	g_object_get(cbuttons[0], "active", &check1, NULL);
	g_object_get(cbuttons[1], "active", &check2, NULL);
	g_object_get(cbuttons[2], "active", &check3, NULL);
	g_object_get(cbuttons[3], "active", &check4, NULL);
	if(check1)
		g_print("Check-Button 1 ist aktiviert\n");
	if(check2)
		g_print("Check-Button 2 ist aktiviert\n");
	if(check3)
		g_print("Check-Button 3 ist aktiviert\n");
	if(check4)
		g_print("Check-Button 4 ist aktiviert\n");
	if(!check1 && !check2 && !check3 && !check4)
		g_print("Kein Check-Button aktiv\n");
	g_print("--------------------------------\n");
}

int main(int argc, char **argv) {
	GtkWindow  *win;
	GdkPixbuf  *pic;
	GtkHBox    *hbox;
	GtkVBox    *vbox[VBOX];
	GtkLabel   *label[LABEL];
	GtkVSeparator *vsep[VBOX-2];
	GtkButton  *buttons[BUTTONS];
	guint i;
	gchar buf[BUF];

	gtk_init( &argc, &argv );
	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	win = g_object_new( GTK_TYPE_WINDOW,
	"title", "Behaelter-Widgets",
	"default-width",  350,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 10,
	"icon", pic,
	NULL );
	/* Eine horizontale Box erzeugen */
	hbox = g_object_new( GTK_TYPE_HBOX,
	"spacing", 10,
	NULL);
	/* VBOX vertikale Boxen erzeugen */
	for(i=0; i < VBOX; i++)
		vbox[i] = g_object_new( GTK_TYPE_VBOX,
		"spacing", 10,
		NULL);
	/* VBOX-2 vertikale Linien erzeugen */
	for(i=0; i < VBOX-2; i++)
		vsep[i] = g_object_new( GTK_TYPE_VSEPARATOR, NULL);
	/* Labels erzeugen */
	label[0] = g_object_new( GTK_TYPE_LABEL,
	"label", "Auswerten der ...",
	NULL);
	label[1] = g_object_new( GTK_TYPE_LABEL,
	"label", "Toogled-Buttons:",
	NULL );
	label[2] = g_object_new( GTK_TYPE_LABEL,
	"label", "Radio-Buttons:",
	NULL);
	label[3] = g_object_new( GTK_TYPE_LABEL,
	"label", "Check-Buttons:",
	NULL );
	/* "normale" Buttons erzeugen */
	buttons[0] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Toggled-Buttons",
	"relief", GTK_RELIEF_HALF,
	NULL );
	buttons[1] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Radio-Buttons",
	"relief", GTK_RELIEF_HALF,
	NULL );
	buttons[2] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Check-Buttons",
	"relief", GTK_RELIEF_HALF,
	NULL );
	buttons[3] = g_object_new( GTK_TYPE_BUTTON,
	"label", "Programmende",
	"relief", GTK_RELIEF_HALF,
	NULL );
	/* BUTTONS Umschalt-Buttons erzeugen */
	for(i = 0; i < BUTTONS; i++) {
		g_snprintf(buf,BUF,"Toggled %d",i+1);
		tbuttons[i] = g_object_new( GTK_TYPE_TOGGLE_BUTTON,
		"label", buf,
		NULL );
	}
	/* BUTTONS Radio-Buttons erzeugen */
	for(i = 0; i < BUTTONS; i++) {
		g_snprintf(buf,BUF,"Radio %d",i+1);
		rbuttons[i] = g_object_new( GTK_TYPE_RADIO_BUTTON,
		"label", buf,
		NULL );
		if(i!=0)
			g_object_set( rbuttons[i],
			"group", rbuttons[0],
			NULL );
		}
	/* BUTTONS Check-Buttons erzeugen */
	for(i = 0; i < BUTTONS; i++) {
		g_snprintf(buf,BUF,"Ckeck %d",i+1);
		cbuttons[i] = g_object_new( GTK_TYPE_CHECK_BUTTON,
		"label", buf,
		NULL );
	}
	/* Signalhandler einrichten */
	g_signal_connect( win, "delete-event",G_CALLBACK(delete_Event), NULL );
	g_signal_connect( win, "destroy",G_CALLBACK(end), NULL );
	/* Signalhandler zum Auswerten der einzelnen */
	/* Buttons einrichten */
	g_signal_connect( buttons[0], "clicked",G_CALLBACK(toogled_auswerten), NULL);
	g_signal_connect( buttons[1], "clicked",G_CALLBACK(radio_auswerten), NULL);
	g_signal_connect( buttons[2], "clicked",G_CALLBACK(check_auswerten), NULL);
	g_signal_connect( buttons[3], "clicked",G_CALLBACK(end), NULL);
	/* Vertikale Boxen und Linien in die horizontalen */
	/* Boxen packen */
	for(i=0; i<VBOX; i++) {
		gtk_box_pack_start_defaults( GTK_BOX(hbox),
		GTK_WIDGET(vbox[i]));
		if(i < VBOX-2)
			gtk_box_pack_start_defaults( GTK_BOX(hbox),
			GTK_WIDGET(vsep[i]));
		}
	/* Beschriftung der ersten vertikalen Box packen */
	gtk_box_pack_start_defaults( GTK_BOX(vbox[0]),
	GTK_WIDGET(label[0]) );
	/* normale Buttons in die erste vertikale Box */
	/* unter der Beschriftung einf�gen */
	for(i = 0; i < BUTTONS; i++)
		gtk_box_pack_start_defaults( GTK_BOX(vbox[0]),
		GTK_WIDGET(buttons[i]) );
	/* Beschriftung der zweiten vertikalen Box packen */
	gtk_box_pack_start_defaults( GTK_BOX(vbox[1]),
	GTK_WIDGET(label[1]));
	/* Umschalt-Buttons in die zweite vertikale Box */
	/* unter der Beschriftung einf�gen */
	for(i = 0; i < BUTTONS; i++)
		gtk_box_pack_start_defaults( GTK_BOX(vbox[1]),
		GTK_WIDGET(tbuttons[i]) );
	/* Beschriftung der dritten vertikalen Box packen */
	gtk_box_pack_start_defaults( GTK_BOX(vbox[2]),
	GTK_WIDGET(label[2]) );
	/* Radio-Buttons in die dritte vertikale Box */
	/* unter der Beschriftung einf�gen */
	for(i = 0; i < BUTTONS; i++)
		gtk_box_pack_start_defaults( GTK_BOX(vbox[2]),
		GTK_WIDGET(rbuttons[i]) );
	/* Beschriftung der vierten vertikalen Box packen */
	gtk_box_pack_start_defaults( GTK_BOX(vbox[3]),
	GTK_WIDGET(label[3]) );
	/* Check-Buttons in die vierte vertikale Box */
	/* unter der Beschriftung einf�gen */
	for(i = 0; i < BUTTONS; i++)
		gtk_box_pack_start_defaults( GTK_BOX(vbox[3]),
		GTK_WIDGET(cbuttons[i]) );
	/* Die horizontale Box in das Hauptfenster packen */
	gtk_container_add(GTK_CONTAINER( win ), GTK_WIDGET( hbox) );
	/* Fenster anzeigen */
	gtk_widget_show_all( GTK_WIDGET(win) );
	/* Hauptschleife von gtk */
	gtk_main();
	g_print("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
