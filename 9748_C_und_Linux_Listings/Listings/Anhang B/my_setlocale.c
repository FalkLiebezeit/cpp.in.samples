/* my_setlocale.c */
#include <stdio.h>
#include <locale.h>
#define KOMMA 3.3223

int main(void) {
	char *local_save = setlocale(LC_ALL, NULL);
	char *local;
	printf("Lokale Umgebung: %s (Standard)\n", local_save);
	printf("Gleitpunkt: %f\n",KOMMA);

	local = setlocale( LC_ALL, "");
	printf("Neue lokale Umgebung: %s\n", local);
	printf("Gleitpunkt: %f\n",KOMMA);

	printf("Standard-Umgebung W iederherstellenwiederherstellen\n");
	local = setlocale( LC_ALL, local_save);
	printf("Lokale Umgebung: %s (W iederhergestelltwiederhergestellt)\n", local);
	return 0;
}

