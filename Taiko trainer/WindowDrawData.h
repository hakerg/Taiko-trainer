#pragma once
#include <allegro5\allegro_font.h>
#include <list>
#include <string>
#include "contants.h"
#include "TaikoCircle.h"

class WindowDrawData
{
public:

	std::list<TaikoCircle> circles;
	double bpm = INIT_BPM;
	std::string message;
	ALLEGRO_FONT * font;
	double katsu_left_intensity = 0.0, don_left_intensity = 0.0, don_right_intensity = 0.0, katsu_right_intensity = 0.0;

	WindowDrawData();
	~WindowDrawData();

	void draw() const;
};
