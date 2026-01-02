/* spaceglider.c */
#include <curses.h>
#include <stdlib.h>
#define QUIT 113   /*'q'*/
#define LEFT 260   /* '<-'*/
#define RIGHT 261  /* '->'*/

static void print_raumschiff (int x) {
	mvdelch (9, x + 2);
	mvdelch (9, x + 1);
	mvdelch (9, x);
	mvdelch (9, x - 1);
	mvdelch (9, x - 2);
	mvaddch (10, x - 1, ACS_LLCORNER);
	mvaddch (10, x + 1, ACS_LRCORNER);
	mvaddch (10, x, ACS_TTEE);
}

int main (void) {
	int x = 40, zufall, c, i;
	srand (79);
	initscr ();
	// Cursor und Funktionstasten ein
	keypad (stdscr, TRUE);
	// keine Ausgabe
	noecho ();
	// Scrolling ein
	scrollok (stdscr, TRUE);
	scroll (stdscr);

	while (c != QUIT) {
		// Eine eine Zeile nach unten scrollen
		scrl (1);
		for (i = 0; i < 5; i++) {
			zufall = rand () % 79;
			mvaddch (20, zufall, '*');
			mvprintw (0, 0,
			"'q' drücken für Quit | Taste für Start | "
			"<- nach links -> nach rechts");
			mvprintw(1,0, "Position Raumschiff %d",x);
		}
		c = getch ();
		halfdelay (3);
		switch (c) {
			case LEFT:
				x--;
				if (x < 0)
					x = 0;
			break;
			case RIGHT:
				x++;
				if (x > 79)
					x = 79;
			break;
			default:
			break;
		}
		print_raumschiff (x);
	}
	endwin ();
	return 0;
}
