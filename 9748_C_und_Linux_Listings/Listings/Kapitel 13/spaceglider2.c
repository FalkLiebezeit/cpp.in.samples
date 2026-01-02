/* spaceglider2.c */
#include <curses.h>
#include <stdlib.h>
#define QUIT 113  // 'q'
#define LEFT 260  // '<-'
#define RIGHT 261 // ->

static void print_raumschiff (int x) {
	mvdelch (9, x + 2);
	mvdelch (9, x + 1);
	mvdelch (9, x);
	mvdelch (9, x - 1);
	mvdelch (9, x - 2);
	/* Raumschiff fette Schrift */
	attrset (A_BOLD | COLOR_PAIR (2));
	mvaddch (10, x - 1, ACS_LLCORNER);
	mvaddch (10, x + 1, ACS_LRCORNER);
	attrset (A_BOLD | COLOR_PAIR (3));
	mvaddch (10, x, ACS_TTEE);
}

int main (void) {
	int x = 40, zufall, c, i;
	srand (79);
	initscr ();
	if (has_colors () == TRUE)
		start_color ();
	else
		exit (EXIT_FAILURE);
	keypad (stdscr, TRUE);
	noecho ();
	scrollok (stdscr, TRUE);
	scroll (stdscr);

	// Farbenpaar Nummer 1
	init_pair (1, COLOR_YELLOW, COLOR_BLACK);
	// Paar Farbenpaar Nummer 2
	init_pair (2, COLOR_RED, COLOR_RED);
	// Farbenpaar Nummer 3
	init_pair (3, COLOR_GREEN, COLOR_BLACK);
	// Farbenpaar Nummer 4
	init_pair (4, COLOR_BLACK, COLOR_GREEN);

	while (c != QUIT) {
		scrl (1);
		for (i = 0; i < 5; i++) {
			zufall = rand () % 79;
			// Sterne dunkel anzeigenusgeg eben
			attrset (A_DIM | COLOR_PAIR (1));
			mvaddch (20, zufall, '*');
			attrset (A_UNDERLINE | A_BOLD | COLOR_PAIR (4));
			mvprintw (0, 0,
			"'q' drücken für Quit | Taste für Start | "
			"<- nach links -> nach rechts");
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
