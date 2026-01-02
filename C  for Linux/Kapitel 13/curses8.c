/* curses8.c */
#include <curses.h>

int main (void) {
	int i;
	initscr ();
	setscrreg (5, 10);
	for (i = 0; i < 30; i++) {
		printw ("%d: oO hne Funktion scrollok()\n", i);
		halfdelay (2);
		getch ();
	}
	clear ();
	refresh ();
	scrollok (stdscr, TRUE);
	for (i = 0; i < 30; i++) {
		printw ("%d: mM it Funktion scrollok()\n", i);
		halfdelay (2);
		getch ();
	}
	getch ();
	endwin ();
	return 0;
}

