/* child2.c */
#include <unistd.h.>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

static int global_var = 1;

int main (void) {
	pid_t pid;
	int lokal_var = 1;

	switch (pid = fork ()) {
		case -1:
			printf ("Fehler bei fork()\n");
			break;
		case 0:
			sleep (1);   /* kurze Pause */
			printf ("--- Im Kindprozess (%d) ---\n",getpid());
			printf ("global_var = %d Speicheradresse : %p\n",
				global_var, &global_var);
			printf ("lokal_var  = %d Speicheradresse ; %p\n",
				lokal_var, &lokal_var);
			fflush(stdout);
			++global_var;
			++lokal_var;
			printf ("--- Im Kindprozess (%d) ---\n",getpid());
			printf ("global_var = %d Speicheradresse : %p\n",
				global_var, &global_var);

			printf ("lokal_var  = %d Speicheradresse ; %p\n",
				lokal_var, &lokal_var);
			fflush(stdout);
		break;
		default:
			printf ("--- Im Elternprozess (%d) ---\n",getpid());
			printf ("global_var = %d Speicheradresse : %p\n",
				global_var, &global_var);
			printf ("lokal_var  = %d Speicheradresse ; %p\n",
				lokal_var, &lokal_var);
			fflush(stdout);
			sleep (2);
			printf ("--- Im Elternprozess (%d) ---\n",getpid());
			printf ("global_var = %d Speicheradresse : %p\n",
				global_var, &global_var);
			printf ("lokal_var  = %d Speicheradresse ; %p\n",
				lokal_var, &lokal_var);
			fflush(stdout);
		break;
	}
	return EXIT_SUCCESS;
}
