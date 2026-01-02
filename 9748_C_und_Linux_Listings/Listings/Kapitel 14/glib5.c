/* glib5.c */
#include <stdio.h>
#include <gtk/gtk.h>
#define MMAX 255

int main(void) {
	const gchar *text = "Hallo ";
	const gchar *tex2 = "Welt! ";
	gchar *copy, *more;
	gchar *str, *test;
	const gchar str1[] = { "String1" };
	const gchar str2[] = { "String2" };
	const gchar str3[] = { "String3" };
	char buf[MMAX];

	copy = g_strdup(text);
	g_print("g_strdup():  %s\n",copy);

	more = g_strdup_printf("%s %s",text, tex2);
	g_print("g_strdup_printf(): %s\n", more);

	str = g_strconcat(str1,"|", str2,"|", str3, NULL);
	g_print("g_strconcat(): %s\n",str);

	str = g_strjoin("|", str1, str2, str3, NULL);
	g_print("g_strjoin(): %s\n", str);

	test = g_malloc(MMAX);
	g_snprintf(test, MMAX, "PIN-Code: 432-557-32 (speichern)");

	g_strdelimit(test, "0123456789", '*');
	g_print("%s\n",test);
	g_print("G_STR_DELIMITERS: %s\n",G_STR_DELIMITERS);

	g_print("Text eingeben: ");
	fgets(buf, MMAX, stdin);
	/* weg mit dem Newline-Zeichen */
	g_strchomp(buf);
	g_print("%s\n",buf);
	g_print("Hinter buf\n");
	return 0;
}

