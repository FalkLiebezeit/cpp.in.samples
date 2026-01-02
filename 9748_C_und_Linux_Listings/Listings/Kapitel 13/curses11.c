/* curses11.c */
#include <curses.h>
#include <stdlib.h>

int main (void) {
	MEVENT pos;
	int l_maus;
	chtype button;

	initscr ();
	noecho ();
	keypad (stdscr, TRUE);
	l_maus = mousemask (BUTTON1_PRESSED, NULL);
	while (1) {
		button = wgetch (stdscr);
		if (button == KEY_MOUSE) {
			if (getmouse (&pos) == OK) {
				wenclose (stdscr, pos.y, pos.x);
				mvwprintw (stdscr, 1, 0, "y = %2d x = %2d",pos.y, pos.x);
			}
		}
		wrefresh (stdscr);
	}
	endwin ();
	return 0;
}

