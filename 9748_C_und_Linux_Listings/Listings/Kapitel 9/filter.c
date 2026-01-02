/* filter.c */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAX 255

/* Filterwörter können angepasst werden. */
const char *filterwords[] = {
	"und", "oder", "aber", "ein", NULL
};
const char token[] = " ";

void output (char *puffer) {
	int i = 0, len;
	static int merker = 0;
	char *p, tmp[20];
	/* Trennen der einzelnen Wörter */
	p = strtok (puffer, token);
	while (p != NULL) {
		i = 0;
		merker = 0;
		while (filterwords[i] != NULL) {
			/* Wir vergleichen alle Wörter, die wir */
			/* ausfiltern wollen, mit dem aktuellen */
			/* Wort, das auf das p zeigt.           */
			if (strstr (p, filterwords[i]) != NULL) {
				len = strlen (filterwords[i]);
				/* Länge des zu ersetzenden Wortes ermitteln */
				memset (tmp, 'x', len);
				tmp[len] = 0;
				/* Jetzt schreiben wir len x in das Array tmp. */
				/* Nun geben wir len x auf dem Bildschirm aus. */
				fputs (tmp, stdout);
				fputs (" ", stdout);   / *Leerzeichen */
				/* Merker, ob schon etwas ausgegeben wurde */
				merker = 1;
			}
			i++;
		}
		if (merker == 0) {
			/* normale Ausgabe, da nichts gefiltert wurde */
			fputs (p, stdout);
			fputs (" ", stdout); / *Leerzeichen */
		}
		p = strtok (NULL, token);
	}
}

int main (void) {
	char pufferin[MAX];
	while (fgets (pufferin, MAX, stdin) != NULL)
		output (pufferin);
	return EXIT_SUCCESS;
}

