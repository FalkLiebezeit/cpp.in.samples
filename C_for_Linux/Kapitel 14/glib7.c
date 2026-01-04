/* glib7.c */
#include <gtk/gtk.h>
#include <stdio.h>

int main (void) {
	GTimer *timer = NULL;
	gdouble time;
	gulong us;
	gint i=300000000;
	gint j=300000000;
	timer = g_timer_new ();

	g_timer_start (timer);
	g_print ("Timer laeuft\n");

	while(i--);
	time = g_timer_elapsed (timer, &us);
	g_print ("Schleife dekrementiert %g sek == %ld usek\n",
		time, us);
	g_timer_reset( timer );
	while(i++ <= j);
	time = g_timer_elapsed (timer, &us);
	g_print ("Schleife inkrementieren %g sek == %ld usek\n",
		time, us);
	g_timer_reset( timer );
	g_print("Timer von Hand starten <ENTER>\n");
	getchar();
	g_timer_start (timer);

	g_print("Timer von Hand stoppen <ENTER>\n");
	getchar();
	g_timer_stop( timer );

	time = g_timer_elapsed (timer, &us);
	g_print ("Vergangene Zeit zwischen Start und Stopp"
		" %g sek == %ld usek\n", time, us);
	g_timer_destroy (timer);
	return 0;
}

