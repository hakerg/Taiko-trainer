#pragma once
#include <allegro5\allegro_font.h>
#include <bass.h>
#include <queue>
#include "AllegroWindow.h"
#include "AnimationExponential.h"
#include "CircleHit.h"
#include "TimeManager.h"
#include "WindowDrawData.h"

class TaikoTrainerWindow : public uc::AllegroWindow<WindowDrawData>
{
public:

	double scrolling_speed = INIT_SROLLING_SPEED, target_scrolling_speed = INIT_SROLLING_SPEED;
	std::chrono::high_resolution_clock::time_point next_circle_time;
	uc::ThreadDataQueue<CircleHit> hits;
	uc::TimeManager value_changers;
	HSTREAM don_hit_sound, katsu_hit_sound, miss_sound, wrong_sound;
	uc::AnimationExponential keys_overlay_animations[4];

	TaikoTrainerWindow();
	~TaikoTrainerWindow();

	typename std::list<TaikoCircle>::iterator closest_circle(std::chrono::high_resolution_clock::time_point time);

	// Odziedziczono za poœrednictwem elementu AllegroWindow
	bool add_time(std::chrono::duration<double> delta_time) override;
	bool _handle_event(const ALLEGRO_EVENT & event) override;
	void draw(const WindowDrawData & source) override;
};