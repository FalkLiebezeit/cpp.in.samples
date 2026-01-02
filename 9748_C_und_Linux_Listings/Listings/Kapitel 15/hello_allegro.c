/* hello_allegro.c */
#include <allegro.h>

int main(void) {
	/* Muss bei jedem Start eines Allegro-Programms
	    verwendet werden */
	if (allegro_init() != 0)
		return 1;
	/* Tastaturhandler einrichten */
	install_keyboard();

	/* Bildschirmmodus auf 320x200 setzen */
	if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
		/* Klappt es mit der Automatik nicht, versuchen
		    wir es mit dem sicheren Modus */
		if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) {
			/* Klappt auch das nicht, zurück in den Textmodus
			    und eine Fehlermeldung ausgeben */
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Konnte den Bildschirmmodus nicht setzen\n%s\n",allegro_error );
			return 1;
		}
	}
	/* Farbpalette einrichten */
	set_palette(desktop_palette);
	/* Bildschirm auf Weiss setzen */
	clear_to_color(screen, makecol(255, 255, 255));
	acquire_screen();
	/* Text mit schwarzer Farbe auf Bildschirm ausgeben */
	textout_centre_ex(screen, font, "Hallo Welt! (Taste druecken)",SCREEN_W/2, SCREEN_H/2, makecol(0,0,0), -1  );
	release_screen();
	/* Warten auf einen Tastendruck */
	readkey();
	return 0;
}
