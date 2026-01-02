/* glib4.c */
#include <gtk/gtk.h>

int main(void) {
	gchar text[]  = { "Text zum Manipulieren" };
	gchar text2[] = { "Text (noch mehr)" };
	g_strup(text);
	g_print("g_strup()  : %s\n",text);
	g_strdown(text);
	g_print("g_strdown(): %s\n",text);
	if(g_strcasecmp( text, text2 ) )
		g_print("'text' und 'text2' sind ungleich\n");
	else
		g_print("Beide Zeichenketten sind gleich\n");
	if(g_strncasecmp(text, text2, 5) )
		g_print("'text' und 'text2' sind ungleich"
		" (erste 5 Zeichen)\n");
	else
		g_print("Die ersten 5 Zeichen der beiden "
		"Strings sind gleich\n");
	g_strreverse( text );
	g_print("g_strreverse() : %s\n",text);
	return 0;
}

