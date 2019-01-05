#include "TaikoCircle.h"
#include <allegro5\allegro_primitives.h>
#include "TaikoTrainerWindow.h"
#include "contants.h"


TaikoCircle::TaikoCircle(std::chrono::high_resolution_clock::time_point hit_time_, float speed_, bool katsu_, bool big_) :
	hit_time(hit_time_), speed(speed_), katsu(katsu_), big(big_)
{
}


TaikoCircle::~TaikoCircle()
{
}

void TaikoCircle::draw() const
{
	al_draw_filled_circle(x(), TARGET_Y, SMALL_CIRCLE_BACKGROUND_RADIUS, CIRCLE_BACKGROUND_COLOR);
	al_draw_filled_circle(x(), TARGET_Y, SMALL_CIRCLE_INNER_RADIUS, katsu ? CIRCLE_KATSU_COLOR : CIRCLE_DON_COLOR);
	al_draw_circle(x(), TARGET_Y, SMALL_CIRCLE_OVERLAY_RADIUS, CIRCLE_OVERLAY_COLOR, SMALL_CIRCLE_OVERLAY_THICKNESS);
}

float TaikoCircle::x() const
{
	return TARGET_X + speed * std::chrono::duration_cast<std::chrono::duration<double>>(hit_time - std::chrono::high_resolution_clock::now()).count();
}
