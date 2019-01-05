#include "TaikoTrainerWindow.h"
#include <allegro5\allegro_ttf.h>
#include "AnimationHalfCosine.h"
#include "contants.h"


TaikoTrainerWindow::TaikoTrainerWindow() :
	AllegroWindow(SCREEN_SIZE, SUB_FRAME_BUFFER_SIZE),
	hits(MAX_REGISTERED_HITS),
	keys_overlay_animations
	{
		{ current_frame.katsu_left_intensity, KEYS_OVERLAY_DAMPING, 0.0 },
		{ current_frame.don_left_intensity, KEYS_OVERLAY_DAMPING, 0.0 },
		{ current_frame.don_right_intensity, KEYS_OVERLAY_DAMPING, 0.0 },
		{ current_frame.katsu_right_intensity, KEYS_OVERLAY_DAMPING, 0.0 }
	}
{
	next_circle_time = std::chrono::high_resolution_clock::now() + READY_TIME;

	don_hit_sound = BASS_StreamCreateFile(false, L"resources//taiko-normal-hitnormal.wav", 0, 0, NULL);
	katsu_hit_sound = BASS_StreamCreateFile(false, L"resources//taiko-normal-hitclap.wav", 0, 0, NULL);
	miss_sound = BASS_StreamCreateFile(false, L"resources//count1s.wav", 0, 0, NULL);
	wrong_sound = BASS_StreamCreateFile(false, L"resources//combobreak.wav", 0, 0, NULL);

	current_frame.font = al_load_ttf_font("resources//consola.ttf", FONT_SIZE, NULL);
}

// Odziedziczono za poœrednictwem elementu AllegroWindow

bool TaikoTrainerWindow::add_time(std::chrono::duration<double> delta_time)
{

	CircleHit hit(std::chrono::high_resolution_clock::now(), false);

	while (hits.try_pop(hit))
	{
		//auto circle_iterator = closest_circle(hit.time);
		auto circle_iterator = current_frame.circles.begin();
		if (circle_iterator == current_frame.circles.end())
		{
			if (hit.katsu) current_frame.message = "katsu";
			else current_frame.message = "don";
		}
		else
		{
			std::chrono::milliseconds hit_delay = std::chrono::duration_cast<std::chrono::milliseconds>(hit.time - circle_iterator->hit_time);
			if (circle_iterator->katsu)
			{
				if (hit.katsu)
				{
					BASS_ChannelPlay(katsu_hit_sound, true);
					current_frame.message = "katsu, delay: " + std::to_string(hit_delay.count()) + "ms";
				}
				else
				{
					BASS_ChannelPlay(wrong_sound, true);
					current_frame.message = "katsu, you hit don";
				}
			}
			else
			{
				if (hit.katsu)
				{
					BASS_ChannelPlay(wrong_sound, true);
					current_frame.message = "don  , you hit katsu";
				}
				else
				{
					BASS_ChannelPlay(don_hit_sound, true);
					current_frame.message = "don  , delay: " + std::to_string(hit_delay.count()) + "ms";
				}
			}
			current_frame.circles.erase(circle_iterator);
		}
	}

	value_changers.add_time(delta_time);
	for (unsigned n = 0; n < 4; n++)
	{
		keys_overlay_animations[n].add_time(delta_time);
	}

	if (std::chrono::high_resolution_clock::now() + CIRCLE_APPEAR_TIME >= next_circle_time)
	{
		current_frame.circles.emplace_back(next_circle_time, scrolling_speed, rand() & 1, false);
		next_circle_time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(15.0 / current_frame.bpm));
	}

	while (current_frame.circles.size())
	{
		if (std::chrono::high_resolution_clock::now() >= current_frame.circles.front().hit_time + CIRCLE_DISAPPEAR_TIME)
		{
			BASS_ChannelPlay(miss_sound, true);
			current_frame.circles.pop_front();
			current_frame.message = "miss";
		}
		else break;
	}

	return true;
}

bool TaikoTrainerWindow::_handle_event(const ALLEGRO_EVENT & event)
{
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return false;
	else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if (event.keyboard.keycode == ALLEGRO_KEY_Z)
		{
			hits.try_push(CircleHit(std::chrono::high_resolution_clock::now(), true));
			current_frame.katsu_left_intensity = 1.0;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_X)
		{
			hits.try_push(CircleHit(std::chrono::high_resolution_clock::now(), false));
			current_frame.don_left_intensity = 1.0;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP)
		{
			hits.try_push(CircleHit(std::chrono::high_resolution_clock::now(), false));
			current_frame.don_right_intensity = 1.0;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_SLASH)
		{
			hits.try_push(CircleHit(std::chrono::high_resolution_clock::now(), true));
			current_frame.katsu_right_intensity = 1.0;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			current_frame.bpm += BPM_STEP;
			current_frame.message = "bpm increased to " + std::to_string(current_frame.bpm);
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			current_frame.bpm -= BPM_STEP;
			current_frame.message = "bpm decreased to " + std::to_string(current_frame.bpm);
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
		{
			target_scrolling_speed += SROLLING_SPEED_STEP;
			value_changers.push_back(std::make_shared<uc::AnimationHalfCosine>(scrolling_speed, target_scrolling_speed - scrolling_speed, std::chrono::seconds(1)));
			current_frame.message = "scrolling speed increased";
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
		{
			target_scrolling_speed -= SROLLING_SPEED_STEP;
			value_changers.push_back(std::make_shared<uc::AnimationHalfCosine>(scrolling_speed, target_scrolling_speed - scrolling_speed, std::chrono::seconds(1)));
			current_frame.message = "scrolling speed decreased";
		}
		return true;
	}
	else return true;
}

void TaikoTrainerWindow::draw(const WindowDrawData & source)
{
	source.draw();
}


TaikoTrainerWindow::~TaikoTrainerWindow()
{
}

typename std::list<TaikoCircle>::iterator TaikoTrainerWindow::closest_circle(std::chrono::high_resolution_clock::time_point time)
{
	auto closest_iterator = current_frame.circles.begin();

	for (auto iterator = current_frame.circles.begin(); iterator != current_frame.circles.end(); iterator++)
	{
		if (abs(iterator->hit_time - time) < abs(closest_iterator->hit_time - time)) closest_iterator = iterator;
	}

	return closest_iterator;
}
