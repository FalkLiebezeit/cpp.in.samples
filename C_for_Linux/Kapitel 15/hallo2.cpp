// hallo2.cpp
#include <stdlib.h>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

void Hallo_cb(Fl_Widget *, void *) {
	printf("Hallo Welt\n"); fflush(stdout);
}

void exit_cb(Fl_Widget *, void *) {
	exit(0);
}

int main(int argc, char ** argv) {
	Fl_Window *window = new Fl_Window(320,65);
	window->label("Ein einfaches FLTK-Beispiel");
	Fl_Button *b1 = new Fl_Button(20, 20, 100, 25, "&Hallo");
	b1->callback(Hallo_cb, 0);
	Fl_Button *b2 = new Fl_Button(200,20, 100, 25, "E&nde");
	b2->callback(exit_cb, 0);
	window->end();
	window->show(argc,argv);
	return Fl::run();
}
