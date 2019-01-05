#include "WindowDrawData.h"
#include <allegro5\allegro_primitives.h>
#include "contants.h"
#include "math_defines.h"



WindowDrawData::WindowDrawData()
{
}


WindowDrawData::~WindowDrawData()
{
}

void WindowDrawData::draw() const
{
	al_clear_to_color(BACKGROUND_COLOR);

	al_draw_filled_rectangle(BLACK_BAR_X1, BLACK_BAR_Y1, BLACK_BAR_X2, BLACK_BAR_Y2, BLACK_BAR_COLOR);

	al_draw_filled_circle(TARGET_X, TARGET_Y, INNER_TARGET_RADIUS, INNER_TARGET_COLOR);
	al_draw_circle(TARGET_X, TARGET_Y, OUTER_TARGET_RADIUS, OUTER_TARGET_COLOR, OUTER_TARGET_THICKNESS);

	for (auto iterator = circles.rbegin(); iterator != circles.rend(); iterator++)
	{
		iterator->draw();
	}

	al_draw_filled_rectangle(PINK_SQUARE_X1, PINK_SQUARE_Y1, PINK_SQUARE_X2, PINK_SQUARE_Y2, PINK_SQUARE_COLOR);
	al_draw_filled_ellipse(KEYS_OVERLAY_X, KEYS_OVERLAY_Y, KEYS_OVERLAY_RADIUS_X, KEYS_OVERLAY_RADIUS_Y, KEYS_OVERLAY_COLOR);


	auto color = CIRCLE_KATSU_COLOR;
	color.r *= katsu_left_intensity;
	color.g *= katsu_left_intensity;
	color.b *= katsu_left_intensity;
	color.a = katsu_left_intensity;
	al_draw_elliptical_arc(KEYS_OVERLAY_X, KEYS_OVERLAY_Y, KEYS_OVERLAY_RADIUS_X, KEYS_OVERLAY_RADIUS_Y, PI_2, PI, color, KEYS_OVERLAY_THICKNESS);
	
	color = CIRCLE_KATSU_COLOR;
	color.r *= katsu_right_intensity;
	color.g *= katsu_right_intensity;
	color.b *= katsu_right_intensity;
	color.a = katsu_right_intensity;
	al_draw_elliptical_arc(KEYS_OVERLAY_X, KEYS_OVERLAY_Y, KEYS_OVERLAY_RADIUS_X, KEYS_OVERLAY_RADIUS_Y, -PI_2, PI, color, KEYS_OVERLAY_THICKNESS);
	
	color = CIRCLE_DON_COLOR;
	color.r *= don_left_intensity;
	color.g *= don_left_intensity;
	color.b *= don_left_intensity;
	color.a = don_left_intensity;
	al_draw_elliptical_arc(KEYS_OVERLAY_X, KEYS_OVERLAY_Y, KEYS_OVERLAY_INNER_RADIUS_X, KEYS_OVERLAY_INNER_RADIUS_Y, PI_2, PI, color, KEYS_OVERLAY_THICKNESS);
	
	color = CIRCLE_DON_COLOR;
	color.r *= don_right_intensity;
	color.g *= don_right_intensity;
	color.b *= don_right_intensity;
	color.a = don_right_intensity;
	al_draw_elliptical_arc(KEYS_OVERLAY_X, KEYS_OVERLAY_Y, KEYS_OVERLAY_INNER_RADIUS_X, KEYS_OVERLAY_INNER_RADIUS_Y, -PI_2, PI, color, KEYS_OVERLAY_THICKNESS);


	al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 30, NULL, "bpm = %i", (int)bpm);
	al_draw_text(font, al_map_rgb(255, 255, 255), 30, 120, NULL, message.c_str());
}
