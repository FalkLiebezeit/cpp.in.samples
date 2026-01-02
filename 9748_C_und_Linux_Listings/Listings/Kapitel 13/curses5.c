/* curses5.c */
#include <curses.h>

int main (void) {
	int i, j;

	initscr ();
	// Ecke links oben
	addch (ACS_ULCORNER);
	// Eine horizontale Linie
	for (i = 0; i < 20; i++)
		addch (ACS_HLINE);
	// Ecke rechts oben
	addch (ACS_URCORNER);
	addch ('\n');
	// vertikale Linie rechts und links (21 Zeilen)
	for (i = 0; i < 10; i++) {
		for (j = 0; j <= 21; j++) {
			if (j == 0)
				addch (ACS_VLINE);
			else if (j == 21) {
				addch (ACS_VLINE);
				addch ('\n');
			}
			else
				addch (' ');
		}
	}
	// Ecke links unten
	addch (ACS_LLCORNER);
	// Eine horizontale Linie
	for (i = 0; i < 20; i++)
		addch (ACS_HLINE);
	// Ecke rechts unten
	addch (ACS_LRCORNER);
	addch ('\n');
	mvprintw (5, 7, "<TASTE>");
	getch ();
	endwin ();
	return 0;
}
