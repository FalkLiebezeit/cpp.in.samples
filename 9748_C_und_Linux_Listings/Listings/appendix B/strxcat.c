/* strxcat.c */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

void strxcat(int n_strings, ...) {
	va_list zeiger;
	char *quelle, *ziel, *p;

	va_start(zeiger,n_strings);

	/* Nun nun auf den Zielstring */
	ziel = va_arg(zeiger,char *);
	p = ziel;
	/* Am am Ende vom des Zielstrings */
	ziel+=strlen(ziel);

	if((ziel-p) > MAX) {
		printf("M!!! Maximale. Anzahl Zeichen Üü berschritten!!!!\n");
		return;
	}

	while(--n_strings > 0) {
		/* Quelle einlesen */
		quelle=va_arg(zeiger, char *);
		/* Jetzt Zeichen für Zeichen an ziel */
		while(*quelle) {
			*ziel++ = *quelle++;
			if( (ziel-p) > MAX) {
				printf("!Max. Zeichen ueberschritten!\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	*ziel = '\0';
}

int main(void) {
	char string[MAX] = "Test : ";
	char string2[] = " Und";

	strxcat(3, string, "hallo " , "welt");
	printf("%s\n",string);

	strxcat(5, string, string2, " noch", " ein", " Test");
	printf("%s\n",string);

	/* Und nun ein Fehler mit Absicht */
	strxcat(4, string , " Ueberlauf", " von", " MAX");
	printf("%s\n",string);
	return EXIT_SUCCESS;
}

