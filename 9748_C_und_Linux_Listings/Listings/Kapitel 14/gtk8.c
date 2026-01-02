/* gtk8.c */
/* Mehrzeiliger Text                   */
/* mit Dateiauswahl - GtkFileSelection */

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

/* Funktionsprototypen */
static GtkWindow *create_window (void);
static void create_tags (GtkTextBuffer * buffer);
static void on_button_clear_clicked (GtkButton * button, gpointer user_data );
static void on_button_cut_clicked (GtkButton * button, gpointer user_data );
static void on_button_copy_clicked (GtkButton * button, gpointer user_data );
static void on_button_paste_clicked (GtkButton * button, gpointer user_data );
static void on_button_bold_clicked (GtkButton * button, gpointer user_data );
static void on_button_underline_clicked (GtkButton * button, gpointer user_data );
static void on_button_strike_clicked (GtkButton * button, gpointer user_data );
static void on_button_color_clicked (GtkButton * button, gpointer user_data );
static void ok_buttonCB (GtkWidget * clicked, GtkWidget * selection);
static void file_open (GtkButton * clicked, GtkWidget * selection);
static void on_button_save_clicked (GtkButton * button, gpointer user_data );

/* Dateiname zum Öffnen */
static gchar *file = NULL;
static GtkTextView *textview;

static GtkWindow * create_window (void) {
	GtkWindow *window;
	GdkPixbuf  *pic;
	GtkVBox *vbox_main;
	GtkToolbar *toolbar;
	GtkWidget *button_clear, *button_cut, *button_copy,
	*button_paste, *button_bold, *button_underline,
	*button_strike, *button_color, *button_open,
	*button_save;
	GtkScrolledWindow *scrolledwindow;
	GtkTextBuffer *buffer;
	GtkFileSelection *fileselect;

	/* Eine Grafik in einen Pixbuf laden */
	pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
	/* Fenster mit folgenden Eigenschaften anlegen */
	window = g_object_new( GTK_TYPE_WINDOW,
	"title", "Textansicht und Textpuffer",
	"default-width",  300,
	"default-height", 200,
	"resizable", TRUE,
	"window-position", GTK_WIN_POS_CENTER,
	"border-width", 0,
	"icon", pic,
	NULL );
	/* eine vertikale Box erzeugen */
	vbox_main = g_object_new( GTK_TYPE_VBOX,
	"spacing", 0,
	NULL);
	/* Eine neue Toolbar erzeugen */
	toolbar = g_object_new (GTK_TYPE_TOOLBAR,
	/* "toolbar-style", GTK_TOOLBAR_ICONS,*/
	NULL);
	/* Buttons mit Stock-Icons für die Toolbar erzeugen */
	button_open = gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-open",
	"Datei oeffnen",
	NULL, NULL, NULL, -1);
	button_save = gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-save",
	"Datei speichern",
	NULL, NULL, NULL, -1);
	button_clear=gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-clear",
	"Text loeschen",
	NULL,NULL,NULL,-1);
	button_cut=gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-cut",
	"Text ausschneiden",
	NULL, NULL, NULL, -1);
	button_copy = gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-copy",
	"Text kopieren",
	NULL, NULL, NULL, -1);
	button_paste=gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-paste",
	"Text einfuegen",
	NULL, NULL, NULL, -1);
	gtk_toolbar_append_space (GTK_TOOLBAR (toolbar));

	button_bold = gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-bold",
	"Fette Schriftart",
	NULL, NULL, NULL, -1);

	button_underline=gtk_toolbar_insert_stock(
	GTK_TOOLBAR (toolbar),
	"gtk-underline",
	"Schrift unterstreichen",
	NULL, NULL, NULL, -1);
	button_strike=gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-strikethrough",
	"Schrift durchstreichen",
	NULL, NULL, NULL, -1);
	button_color=gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
	"gtk-select-color",
	"farbige Schrift (Blau)",
	NULL, NULL, NULL, -1);
	/* Rollbalken erzeugen */
	scrolledwindow = g_object_new( GTK_TYPE_SCROLLED_WINDOW,
	"hscrollbar_policy" , GTK_POLICY_AUTOMATIC,
	"vscrollbar_policy" , GTK_POLICY_AUTOMATIC,
	"window_placement"  , GTK_CORNER_TOP_LEFT,
	NULL);
	/* Eine Textansicht erzeugen */
	textview = g_object_new( GTK_TYPE_TEXT_VIEW, NULL);
	/* Aktuellen Puffer für die Textansicht ermitteln */
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	/* Einige einfache Tags zur Formatierung anlegen */
	create_tags (buffer);
	/* Dateiauswahlbox erzeugen */
	fileselect = g_object_new( GTK_TYPE_FILE_SELECTION,
	"filename" ,"Bitte Datei auswaehlen ...",
	"select-multiple", FALSE,
	"show-fileops"  , TRUE,
	NULL);
	/* Signalhandler einrichten */
	g_signal_connect ( (gpointer) window, "delete_event",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect ( (gpointer) button_clear, "clicked",G_CALLBACK (on_button_clear_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_cut, "clicked",G_CALLBACK (on_button_cut_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_copy, "clicked",G_CALLBACK (on_button_copy_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_paste, "clicked",G_CALLBACK (on_button_paste_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_bold, "clicked",G_CALLBACK (on_button_bold_clicked),(gpointer) textview);

	g_signal_connect ( (gpointer) button_underline, "clicked",G_CALLBACK (on_button_underline_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_strike, "clicked",G_CALLBACK (on_button_strike_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_color, "clicked",G_CALLBACK (on_button_color_clicked),(gpointer) textview);
	g_signal_connect ( (gpointer) button_save, "clicked",G_CALLBACK (on_button_save_clicked),(gpointer) textview);
	g_signal_connect (GTK_OBJECT(GTK_FILE_SELECTION (fileselect)->ok_button),"clicked", G_CALLBACK(ok_buttonCB), fileselect);
	g_signal_connect_swapped (
		GTK_OBJECT(GTK_FILE_SELECTION (fileselect)->ok_button),
		"clicked",
		G_CALLBACK(gtk_widget_hide),
		GTK_OBJECT (fileselect));
	g_signal_connect_swapped (
		GTK_OBJECT(GTK_FILE_SELECTION (fileselect)->cancel_button),
		"clicked",
		G_CALLBACK(gtk_widget_hide),
		GTK_OBJECT (fileselect));
	g_signal_connect (GTK_OBJECT(button_open), "clicked",G_CALLBACK (file_open), fileselect);
	/* Alles packen */
	gtk_container_add( GTK_CONTAINER (window),GTK_WIDGET(vbox_main) );
	gtk_box_pack_start ( GTK_BOX (vbox_main),GTK_WIDGET(toolbar),FALSE, FALSE,0);
	gtk_box_pack_start ( GTK_BOX (vbox_main),GTK_WIDGET(scrolledwindow),TRUE,TRUE, 0);
	gtk_container_add ( GTK_CONTAINER (scrolledwindow), GTK_WIDGET(textview));
	/* Erzeugtes Fenster zurückgegeben */
	return window;
}

/* Datei zum Lesen öffnen */
static void ok_buttonCB (GtkWidget * clicked, GtkWidget * selection) {
	FILE *f;
	gchar buf[255];
	GtkTextBuffer *buffer = NULL;
	GtkTextIter end;

	file=gtk_file_selection_get_filename (GTK_FILE_SELECTION(selection));
	if (file == NULL)
		return; /* Datei existiert nicht */
	f = fopen (file, "r");
	if (NULL == f) {
		printf("Keine solche Datei vorhanden!!\n");
		return;
	}
	else {
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview) );
		while(fgets(buf,255,f)) {
			gtk_text_buffer_get_end_iter(buffer, &end);
			gtk_text_buffer_insert(buffer, &end, buf, –1);
		}
	}
	fclose (f);
}

static void file_open (GtkButton * clicked, GtkWidget * selection) {
	GtkTextBuffer *buffer = NULL;
	/* Neue Datei öffnen, daher:
	  + Dateinamen auf NULL setzen
	  + Inhalt von bereits vorhandenem Text löschen */
	file = NULL;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_set_text(buffer,"", –1);
	gtk_widget_show (selection);
}

/* Datei abspeichern */
static void on_button_save_clicked (GtkButton * button, gpointer user_data) {
	GtkTextBuffer *buffer = NULL;
	GtkTextIter start, end;
	gchar *buf;
	gchar *dyn;
	FILE *f;

	if(file != NULL) {
		/* Aktuellen Puffer für die Textansicht ermitteln */
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (user_data) );
		/* Markierte Auswahl im Puffer ermitteln */
		gtk_text_buffer_get_bounds (buffer, &start, &end);
		/* Zeiger auf den kompletten Text zurück */
		buf=gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
		dyn = g_malloc( strlen(buf)+1 );
		g_stpcpy( dyn, buf );
		/* Zur Kontrolle Ausgabe auf die Konsole */
		g_print("%s\n... gespeichert!\n",dyn);
		f = fopen(file, "w");
		if(f != NULL)
			fwrite(dyn, strlen(dyn)+1, 1, f);
		fclose(f);
	}
}

int main (int argc, char **argv) {
	GtkWindow *window;
	gtk_init (&argc, &argv);
	window = create_window ();
	gtk_widget_show_all (GTK_WIDGET(window));
	gtk_main ();
	return 0;
}
