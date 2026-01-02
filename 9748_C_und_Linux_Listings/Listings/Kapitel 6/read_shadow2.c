/* read_shadow2.c */
/* Programm benötigt Superuser-Rechte.  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <shadow.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct spwd *shadow_ptr;
	if( argc != 2 ) {
		fprintf(stderr, "Usage: %s Name\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	shadow_ptr=getspnam(argv[1]);
	if(shadow_ptr == NULL) {
		printf("Konnte nichts über %s ermitteln\n", argv[1]);
		exit (EXIT_FAILURE);
	}
	printf("Folgendes wurde zu %s ermittelt: \n", argv[1]);
	printf("Benutzername              : %s\n",
		shadow_ptr->sp_namp);
	printf("Passwort (verschlüsselt)   : %s\n",
		shadow_ptr->sp_pwdp);
	printf("Tag der letzten Änderung  : %li Tage\n",
		shadow_ptr->sp_lstchg);
	printf("Nächste Änderung möglich  : %li Tage\n",
		shadow_ptr->sp_min);
	printf("Nächste Änderung fällig   : %li Tage\n",
		shadow_ptr->sp_max);
	printf("Warnung, wenn Passwort fällig, %li Tage zuvor!\n",
		shadow_ptr->sp_warn);
	printf("Konto nach %li Tagen vor Ablauf der Frist sperren!\n",
		shadow_ptr->sp_inact);
	return EXIT_SUCCESS;
}
