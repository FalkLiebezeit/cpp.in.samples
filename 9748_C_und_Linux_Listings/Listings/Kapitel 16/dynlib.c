/* dynlib.c */
#include <stdio.h>
#include <stdlib.h>
#include <myequal.h>
#include <dlfcn.h>
#define LIBEQUAL "libequal.so"

/* dynamische Bibliothek laden */
static void *my_load_dyn (const char *lib) {
	static void *handle;
	handle = dlopen (LIBEQUAL, RTLD_NOW);
	if (handle == NULL) {
		printf ("Fehler bei dlopen(): %s\n", dlerror ());
		exit (EXIT_FAILURE);
	}
	return handle;
}

/* Funktion aus der dynamischen Bibliothek laden */
static void *my_load_func (void *handle, const char *func) {
	void *funcptr = dlsym (handle, func);
	if (funcptr == NULL) {
		printf ("Fehler bei dlsym(): %s\n", dlerror ());
		exit (EXIT_FAILURE);
	}
	return funcptr;
}

/* Speicher wieder freigeben */
static void my_close_func (void *handle) {
	if (dlclose (handle))
		printf ("Fehler bei dlclose(): %s\n", dlerror ());
}

int main (void ) {
	MYBOOL ret;
	void *lib_handle;
	int (*equal) (int a, int b);
	int val1=1 ,val2 = 1;

	while ( 1 ) {
		printf ("Erste Zahl 1  eingeben: ");
		scanf ("%d", &val1);
		printf ("ZweiteZahl Zahl2 eingeben: ");
		scanf ("%d", &val2);
		if( val1 == 0 || val2 ==0 )
			break;
		lib_handle = my_load_dyn (LIBEQUAL);
		equal = my_load_func (lib_handle, "my_equal");
		ret = (*equal) (val1, val2);
		if (ret == MYTRUE)
			printf ("Beide Werte sind gleich\n");
		else
			printf ("Die Werte sind nicht gleich\n");
		my_close_func (lib_handle);
	}
	return EXIT_SUCCESS;
}
