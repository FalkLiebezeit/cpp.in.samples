/* gtk9.c */
#include <gtk/gtk.h>
#define LEFTBUT   1
#define MIDDLEBUT 2
#define RIGHTBUT  3

static gint delete_Event(GtkWidget *widget, GdkEvent *event, gpointer data) {
	return FALSE;
}

static void exitCB (GtkButton * clicked, gpointer data) {
	gtk_main_quit ();
}

static gboolean show_pos (GtkWidget *widget, GdkEventButton *event, GtkWidget *label ) {
	const gchar *button[] = {
		 NULL, "linker Button", "mittlerer Button","rechter Button"
	};
	gint x = event->x;
	gint y = event->y;
	gint z = event->button;
	gchar *pos = g_strdup_printf ("Event: %d, %d (%s)\n", x, y, button[z]);
	gtk_label_set_text (GTK_LABEL (label), pos);
	return TRUE;
}

static gboolean change_label1 (GtkWidget* widget, GdkEventButton* event, GtkWidget *label ) {
	const gchar *new_label = {
		"Event : Mauscursor tritt ins Fenster ein\n"
	};
	gtk_label_set_text (GTK_LABEL (label), new_label);
	return TRUE;
}

static gboolean change_label2 (GtkWidget * widget, GdkEventButton * event, GtkWidget * label) {
	const gchar *new_label = {
		"Event : Mauscursor hat Fenster verlassen\n"
	};
	gtk_label_set_text (GTK_LABEL (label), new_label);
	return TRUE;
}

static gboolean key_press (GtkWidget * widget, GdkEventKey * event, GtkWidget * label) {
	gchar *new_label = g_strdup_printf ("Event : Taste '%s' (Wert:%d) wurde gedrueckt\n",event->string, event->keyval);
	gtk_label_set_text (GTK_LABEL (label), new_label);
	return TRUE;
}

int main (int argc, char **argv) {
	GtkWidget *fenster;
	GtkWidget *label;
	/*Gtk initialisieren */
	gtk_init (&argc, &argv);
	/*Ein neues Fenster erstellen */
	fenster = g_object_new( GTK_TYPE_WINDOW,
	"title", "Verschiedene Anzeigeelemente",
	"default-width",  300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 5,
	NULL );
	label = g_object_new( GTK_TYPE_LABEL, NULL);

	/* Versuch, über den Window-Manager zu beenden */
	g_signal_connect ( GTK_OBJECT (fenster), "delete-event",G_CALLBACK (delete_Event), NULL);
	g_signal_connect ( GTK_OBJECT (fenster), "destroy",G_CALLBACK (exitCB), NULL);
	/* Callbacks für die Events einrichten */
	g_signal_connect (GTK_OBJECT (fenster), "button-press-event",G_CALLBACK (show_pos), label);
	g_signal_connect ( GTK_OBJECT (fenster), "enter-notify-event",G_CALLBACK(change_label1), label);
	g_signal_connect ( GTK_OBJECT (fenster), "leave-notify-event",G_CALLBACK (change_label2), label);
	g_signal_connect ( GTK_OBJECT (fenster), "key-press-event",G_CALLBACK (key_press), label);
	gtk_widget_set_events (fenster,
	GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK
	| GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK
	| GDK_KEY_PRESS_MASK);
	gtk_container_add (GTK_CONTAINER (fenster), label);
	/* Zeigs uns ... */
	gtk_widget_show_all (fenster);
	gtk_main ();
	return 0;
}

