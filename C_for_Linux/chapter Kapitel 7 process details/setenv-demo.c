/* setenv-demo.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
/* vorhandene Variable nicht überschreiben */
#define PROTECT_ON  0
/* überschreiben ... */
#define PROTECT_OFF 1

int main (void) {
	char name[MAX], neu_wert[MAX];

	printf("Umgebungsvariable: ");
	scanf("%254s",name);
	printf("Wert       : %s\n", getenv(name));

	printf("Wert ändern/setzen durch : ");
	scanf("%254s",neu_wert);
	if( setenv( name, neu_wert, PROTECT_OFF ) != 0 )
		printf("Konnte neuen Wert nicht setzen\n");

	printf("Neuer Wert (%s) : %s\n", name, getenv(name));
	return EXIT_SUCCESS;
}
