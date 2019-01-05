#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <bass.h>
#include "TaikoTrainerWindow.h"

int main()
{

	BASS_Init(-1, 48000, NULL, NULL, NULL);

	TaikoTrainerWindow::init_allegro();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

	TaikoTrainerWindow window;
	window.run(window.sub_frame_period(60.0));

	//system("pause");

	return 0;
}