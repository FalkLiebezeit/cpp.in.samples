/* my_getch.c */
#include <stdio.h>
#include <unistd.h.>
#include <termios.h>
#include <stdlib.h>

static struct termios new_io;
static struct termios old_io;

/* Funktion schaltet das Terminal in den Raw-Modus:            */
/* Folgende Eingabeflags werden gelöscht:                      */
/*               BRKINT, ICRNL, INPCK, ISTRIP, IXON            */
/* Folgende Kontrollflags werden gelöscht: CSIZE, PERENB       */
/* Folgende Ausgabeflags werden gelöscht: OPOST                */
/* Folgende lokale Flags werden gelöscht:                      */
/*                           ECHO, ICANON, IEXTEN, ISIG        */
/* Gesetzt wird das Kontrollflag CS8, was bedeutet,            */
/* dass ein Zeichen 8 Bit breit ist.                            */
/* Steuerzeichen: Leseoperation liefert 1 Byte VMIN=1 VTIME=1  */
static int raw (int fd) {
	/* Sichern unseres Terminals */
	if ((tcgetattr (fd, &old_io)) == -1)
		return -1;
	new_io = old_io;
	/* Wir verändern jetzt die Flags für den Raw-Modus. */
	new_io.c_iflag =
		new_io.c_iflag & ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	new_io.c_oflag = new_io.c_iflag & ~(OPOST);
	new_io.c_cflag = new_io.c_cflag & ~(CSIZE | PARENB);
	new_io.c_lflag = new_io.c_lflag & ~(ECHO|ICANON|IEXTEN|ISIG);
	new_io.c_cflag = new_io.c_cflag | CS8;
	new_io.c_cc[VMIN]  = 1;
	new_io.c_cc[VTIME] = 0;
	/* Jetzt setzen wir den Raw-Modus. */
	if ((tcsetattr (fd, TCSAFLUSH, &new_io)) == -1)
		return -1;
	return 0;
}

/* Funktion zur Abfrage einer Taste */
static int getch () {
	int c;
	if (raw (STDIN_FILENO) == -1) {
		printf ("Fehler bei der Funktion raw()\n");
		exit (EXIT_FAILURE);
	}
	c = getchar ();
	/* Alten alten Terminalmodus wiederherstellen */
	tcsetattr (STDIN_FILENO, TCSANOW, &old_io);
	return c;
}

int main (void) {
	int zeichen;
	printf ("Warte auf ' q', um das Programm zu beenden\n");
	while ((zeichen = getch ()) != 'q')
		printf ("'%c' != 'q'\n", zeichen);
	printf ("'%c' == 'q'\n", zeichen);
	printf ("ENDE\n");
	return EXIT_SUCCESS;
}
