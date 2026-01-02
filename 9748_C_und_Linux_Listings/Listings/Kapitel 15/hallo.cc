/*hallo.cc */
#include <gtkmm.h>
#include <iostream>
using namespace Gtk;

// Der Signal-Handler
void button_angeklickt() {
	std::cout << "Hilfe wurde gedrückt" << std::endl;
}

int main( int argc, char *argv[] ) {
	// Das Gtk::Main-Objekt wird für alle
	// gtkmm-Anwendungen benötigt
	Main kit( argc, argv );

	// Das Hauptfenster Gtk::Windo
	Window window;
	window.set_title("Ein leeres Fenster");
	window.set_default_size( 300, 200 );
	window.set_border_width(15);

	// Ein Textlabel (Gtk::Label)
	Label lab("gtkmm mit Label und Button");
	// Zwei Buttons (Gtk::Button)
	Button ende_but(Stock::QUIT);
	Button hilfe("HILFE");
	// Signal-Handler für Buttons einrichten -
	// Programm beenden
	ende_but.signal_clicked().connect(sigc::ptr_fun(&Gtk::Main::quit) );
	hilfe.signal_clicked().connect(sigc::ptr_fun(&button_angeklickt));

	// Alles in eine vertikale Box packen (Gtk::VBox)
	VBox vbox(false, 15);
	vbox.add(lab);
	vbox.add(ende_but);
	vbox.add(hilfe);

	//Box in das Hauptfenster packen
	window.add(vbox);
	// Alle Widgets anzeigen
	window.show_all();
	// Alles anzeigen und die Event-
	//Verarbeitungsschleife starten
	Main::run(window);
	return 0;
}
