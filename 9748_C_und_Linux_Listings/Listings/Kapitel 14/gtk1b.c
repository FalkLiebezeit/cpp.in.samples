/* gkt1b.c */
/* Ein leeres Fenster und eine Dialogbox */
#include <gtk/gtk.h>

static GtkWindow *win;

static gint delete_Event(GtkWidget * widget, GdkEvent event, gpointer daten){
	GtkWidget *dialog, *label;
	gint result;

	/* Eine neue Dialogbox erzeugen */
	dialog = gtk_dialog_new_with_buttons (
	"Sind Sie sicher?",
	win,
	GTK_DIALOG_DESTROY_WITH_PARENT,
	"Ja", GTK_RESPONSE_ACCEPT,
	"Nein", GTK_RESPONSE_REJECT,
	NULL);
	/* Ein Label dazu */
	label = gtk_label_new ("Wollen Sie das Programm wirklich beenden?");

	/* Label in die vorhandene (Standard-)Box (vertikal) */
	/* von der Dialogbox packen                          */
	gtk_container_add( GTK_CONTAINER( GTK_DIALOG( dialog )->vbox),label);
	/* Dialogbox anzeigen */
	gtk_widget_show_all (dialog);
	/* Wartet auf eine Eingabe in der Dialogbox des Anwenders */
	result = gtk_dialog_run (GTK_DIALOG (dialog));

	switch (result) {
		case GTK_RESPONSE_ACCEPT: /* Ja-Button wurde gedrückt */
			g_print("GTK_RESPONSE_ACCEPT\n");
			/* Dialogbox zerstören */
			gtk_widget_destroy (dialog);
			/* Hauptfenster auch zerstören */
			return FALSE;
		break;
		case GTK_RESPONSE_REJECT:
			g_print("GTK_RESPONSE_REJECT\n");
			/* Dialogbox zerstören */
			gtk_widget_destroy (dialog);
			/* Hauptfenster nicht zerstören */
			return TRUE;
		break;
		case GTK_RESPONSE_DELETE_EVENT:
			g_print("GTK_RESPONSE_DELETE_EVENT\n");
			/* Dialogbox zerstören */
			gtk_widget_destroy (dialog);
			/* Hauptfenster nicht zerstören */
			return TRUE;
		break;
		default:
			g_print("Fehler beim Auswerten der Dialogbox?\n");
			return TRUE;
	}
}

static void end (GtkWidget * widget, gpointer daten) {
	g_print ("Und tschuess!\n");
	/* Die Verarbeitungsschleife beenden */
	gtk_main_quit ();
}

int main (int argc, char **argv) {
	/* 1. Die Umgebung initialisieren */
	gtk_init (&argc, &argv);
	/* 2. Die Widgets erzeugen */
	/* 2a. Fenster mit den folgenden Eigenschaften ... anlegen */
	win = g_object_new (GTK_TYPE_WINDOW,
	"title", "Ein leeres Fenster",
	"default-width", 300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 5, NULL);
	/* 3. Signalhandler (Callback-Funktion) einrichten */
	g_signal_connect ( win, "delete-event",G_CALLBACK (delete_Event), NULL );
	g_signal_connect ( win, "destroy",G_CALLBACK (end), NULL );
	/* 4. Hier gibt es noch nichts zum Packen */
	/* 5. (Widgets-)Fenster anzeigen */
	gtk_widget_show_all (GTK_WIDGET (win));
	/* 6. Hauptschleife von gtk-Verarbeitungsschleife */
	gtk_main ();
	g_print ("Die GTK-Hauptschleife wurde beendet\n");
	return 0;
}
