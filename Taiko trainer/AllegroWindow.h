#pragma once
#include <allegro5/allegro.h>
#include "AllegroBitmap.h"
#include "Transformation.h"
#include "Vector2D.h"
#include "Window.h"

namespace uc
{

	template <class _Drawable>
	class AllegroWindow : public Window<_Drawable, AllegroBitmap>
	{

		bool _acknowledge_drawing_halt = false;

		ALLEGRO_EVENT_QUEUE * _queue;

		// thread #1
		bool _parse_event() override
		{

			ALLEGRO_EVENT event;
			if (al_get_next_event(_queue, &event))
			{
				if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) al_acknowledge_resize(k_display);
				else if (event.type == ALLEGRO_EVENT_DISPLAY_LOST) this->visible = false;
				else if (event.type == ALLEGRO_EVENT_DISPLAY_FOUND) this->visible = true;
				else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT) this->visible = false;
				else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) this->visible = true;
				else if (event.type == ALLEGRO_EVENT_DISPLAY_HALT_DRAWING)
				{
					this->visible = false;
					_acknowledge_drawing_halt = true;
				}
				else if (event.type == ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING)
				{
					this->visible = true;
					al_acknowledge_drawing_resume(k_display);
				}
				return _handle_event(event);
			}
			else std::this_thread::sleep_for(std::chrono::milliseconds(1));

			return true;
		}

		// main thread
		void _finish_frame() override
		{
			al_flip_display();
			if (_acknowledge_drawing_halt)
			{
				al_acknowledge_drawing_halt(k_display);
				_acknowledge_drawing_halt = false;
				while (!this->visible) std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		// main thread
		std::unique_ptr<AllegroBitmap> _create_buffer_image(const Vector2D<unsigned> & size) const override
		{
			return std::make_unique<AllegroBitmap>(size);
		}

		// main thread
		void _draw(const AllegroBitmap & source, float alpha) override
		{
			al_set_target_backbuffer(k_display);
			al_draw_tinted_bitmap(source.k_bitmap, al_map_rgba_f(alpha, alpha, alpha, alpha), 0, 0, NULL);
		}
		void _draw(const _Drawable & source) override
		{
			al_set_target_backbuffer(k_display);
			draw(source);
		}
		void _draw(const _Drawable & source, AllegroBitmap & target) override
		{
			al_set_target_bitmap(target.k_bitmap);
			draw(source);
		}

		virtual bool _handle_event(const ALLEGRO_EVENT & event) = 0; // thread #1

	public:

		ALLEGRO_DISPLAY * const k_display;


		AllegroWindow(const Vector2D<unsigned> & size_, unsigned buffered_frames_) :
			Window<_Drawable, AllegroBitmap>(buffered_frames_),
			k_display(al_create_display(size_.x, size_.y)),
			_queue(al_create_event_queue())
		{
			al_register_event_source(_queue, al_get_display_event_source(k_display));

			al_register_event_source(_queue, al_get_mouse_event_source());
			al_register_event_source(_queue, al_get_keyboard_event_source());
			al_register_event_source(_queue, al_get_joystick_event_source());
			al_register_event_source(_queue, al_get_touch_input_event_source());
		}

		virtual ~AllegroWindow()
		{

			al_destroy_event_queue(_queue);
			al_destroy_display(k_display);

		}

		static void init_allegro()
		{
			al_init();
			al_install_keyboard();
			al_install_mouse();
			al_install_joystick();
			al_install_touch_input();
		}

		Vector2D<unsigned> size() const override
		{
			return { (unsigned)al_get_display_width(k_display), (unsigned)al_get_display_height(k_display) };
		}

		unsigned framerate() const
		{
			return al_get_display_refresh_rate(k_display);
		}

		// use source as input drawing data
		// there is no need to call al_flip_display() and set_target_backbuffer(...), but
		// whole frame should be cleared before drawing
		virtual void draw(const _Drawable & source) = 0;

		// coordinates of screen borders
		Rectangle<double> window_bounds() const
		{
			auto s = size();
			return { s * 0.5, s };
		}

		// coordinates of a square at the center of the screen
		// use it with Transformation to normalize coordinates at the screen
		// i.e.:
		// normalized_position = Transformation::fit_position(screen_position, min_bounds(), Rectangle<double>(Vector2D<double>(0.5, 0.5), Vector2D<double>(1.0, 1.0)));
		// or
		// screen_position = Transformation::fit_position(normalized_position, Rectangle<double>(Vector2D<double>(0.5, 0.5), Vector2D<double>(1.0, 1.0)), min_bounds());
		Rectangle<double> bounds(double dimension) const
		{
			return { size() * 0.5, { dimension, dimension } };
		}

		// fit screen
		Rectangle<double> min_bounds() const
		{
			return bounds(this->min_dimension());
		}

		// expand screen
		Rectangle<double> max_bounds() const
		{
			return bounds(this->max_dimension());
		}

		// balance between fit and expand
		Rectangle<double> average_bounds() const
		{
			return bounds(size().quadrature());
		}

	};

}