/* curses12.c */
#include <curses.h>
#include <stdlib.h>

int main (void) {
	MEVENT pos;
	int l_maus;
	chtype button;
	initscr ();
	noecho ();
	keypad (stdscr, TRUE);
	l_maus = mousemask( BUTTON1_RELEASED | BUTTON1_PRESSED | BUTTON1_CLICKED, NULL);
	while (1) {
		button = wgetch (stdscr);
		clear ();
		if (button == KEY_MOUSE) {
			if (getmouse (&pos) == OK) {
				// linke Maustaste gedrückt ...
				if (pos.bstate == BUTTON1_PRESSED) {
					wenclose (stdscr, pos.y, pos.x);
					mvwprintw (stdscr, 1, 0,"linke Maustaste gedrückt bei y = %2d x = %2d",pos.y, pos.x);
				}
				// linke Maustaste losgelassen ...
				if (pos.bstate == BUTTON1_RELEASED) {
					// Reaktionszeit eine Tausendstelsekunde setzen
					mouseinterval (1);
					wenclose (stdscr, pos.y, pos.x);
					mvwprintw (stdscr, 2, 0,"linke Maustaste losgelassen y = %2d x = %2d",pos.y, pos.x);
				}
			}
		}
		wrefresh (stdscr);
	}
	endwin ();
	return 0;
}
