// hallo_qt/main.cpp
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QWidget* win        = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout(win);
	QPushButton* but1   = new QPushButton("Über Qt");
	QPushButton* but2   = new QPushButton("Beenden");

	// Größe der Buttons
	but1->resize(120, 30);
	but2->resize(120, 30);

	// Widgets zur vertikalen Box hinzufügen
	layout->addWidget(but1);
	layout->addWidget(but2);

	// Signal-und-Slot-Verbindungen herstellen
	QObject::connect( but1, SIGNAL( clicked() ),&app, SLOT( aboutQt() ) );
	QObject::connect( but2, SIGNAL( clicked() ),&app, SLOT( quit() ) );

	// Fenster anzeigen
	win->show();
	return app.exec();
}
