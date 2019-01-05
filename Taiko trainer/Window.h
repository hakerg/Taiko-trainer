#pragma once
//#include <algorithm>
//#include <iostream>
#include <memory>
#include "LoopedThread.h"
#include "ThreadDataQueue.h"
#include "TimeDependent.h"

namespace uc
{

	// use current_frame to modify drawing data of the frame
	//
	// drawing procedure works as below:
	//
	//  - add_time is called - this method controls whole game engine
	//  - current_frame is pushed to sub-frame buffer
	//  - when main thread finishes drawing previous frame, all frames from sub-frame are then combined into one and drawn
	// (regardless of current buffer size)
	//
	//  another thread controls events
	//

	template <class _Drawable, class _BufferImage>
	class Window :
		public TimeDependent
	{

		// thread #2
		bool _push_next_sub_frame()
		{

			if (add_time(sub_frame_pusher->period) && _event_handler->running)
			{

				if (visible)
				{

					if (dropping_frames_allowed)
					{
						if (!sub_frame_buffer.full())
						{
							sub_frame_buffer.try_push(current_frame);
						}
					}
					else
					{
						while (!sub_frame_buffer.try_push(current_frame))
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(1));
						}
					}

				}

				return true;

			}
			else return false;
		}

		// draw source to the window
		// use source as input drawing data
		virtual void _draw(const _Drawable & source) = 0; // main thread

		// use source as input drawing data
		virtual void _draw(const _Drawable & source, _BufferImage & target) = 0; // main thread

		// draw source image to the window with some opacity
		virtual void _draw(const _BufferImage & source, float alpha) = 0; // main thread

		// used to create motion-blur effect
		virtual std::unique_ptr<_BufferImage> _create_buffer_image(const Vector2D<unsigned> & size) const = 0; // main thread


		// main thread
		bool _draw_frame()
		{

			if (sub_frame_pusher->running)
			{

				if (sub_frame_buffer.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(1));
				else
				{

					unsigned sub_frames = sub_frame_buffer.size();

					//std::cout << sub_frames << std::endl;

					_draw(sub_frame_buffer.front());
					sub_frame_buffer.try_pop();

					if (sub_frames > 1)
					{

						if (!_buffer_image) _buffer_image = _create_buffer_image(size());
						else if (_buffer_image->size() != size()) _buffer_image = _create_buffer_image(size());

						float max_divider = min((float)sub_frames, 256.0f);
						for (float divider = 2.0f; divider <= max_divider; divider++)
						{
							_draw(sub_frame_buffer.front(), *_buffer_image);
							sub_frame_buffer.try_pop();
							_draw(*_buffer_image, 1.0f / divider);
						}

					}

					_finish_frame();
				}

				return true;
			}
			else
			{
				sub_frame_buffer.clear();
				return false;
			}

		}

		virtual bool _parse_event() = 0; // thread #1

		// called when frame is ready to flip
		virtual void _finish_frame() = 0; // main thread

		std::unique_ptr<_BufferImage> _buffer_image;
		std::unique_ptr<LoopedThread> _event_handler;

	public:
		ThreadDataQueue<_Drawable> sub_frame_buffer;
		std::unique_ptr<LoopedThread> sub_frame_pusher;
		bool dropping_frames_allowed = false;
		bool visible = true;
		_Drawable current_frame;

		// opens a new window
		// buffered_frames - determines the maximum number of sub-frames rendered per one frame
		// all sub-frames are being combined to render frame with motion-blur effect
		// first sub-frame is drawn directly on the screen without mediation of buffered frame image
		// set buffered_frames to 1 and dropping_frames_allowed to true if you want to enable default drawing behaviour
		// high values will decrease fps
		Window(unsigned buffered_frames_) : sub_frame_buffer(buffered_frames_) {}
		virtual ~Window() {}

		virtual Vector2D<unsigned> size() const = 0;

		// min(size.x, size.y)
		unsigned min_dimension() const
		{
			auto s = size();
			return min(s.x, s.y);
		}

		// max(size.x, size.y)
		unsigned max_dimension() const
		{
			auto s = size();
			return max(s.x, s.y);
		}

		// use frame_period or sub_frame_period to calculate period
		// add_time is called with constant delta_time before every sub-frame
		// if you set the period to 0, frames will be drawn at full speed and delta_time in add_time will be set to 0
		// ends when event handler or frame pusher return false, but does not close the window
		// this method can be called multiple times, however this is not recommended
		template <class _Rep, class _Period>
		void run(std::chrono::duration<_Rep, _Period> sub_frame_period)
		{
			_event_handler = std::make_unique<LoopedThread>(std::chrono::duration<double>::zero(), false, this, &Window::_parse_event);

			sub_frame_pusher = std::make_unique<LoopedThread>(sub_frame_period, true, this, &Window::_push_next_sub_frame);

			while (_draw_frame());

			sub_frame_pusher.reset();
			_event_handler.reset();

		}

		// time of one frame
		// if you set fps to display refresh rate, one sub-frame corresponds to one frame
		static std::chrono::duration<double> frame_period(double fps)
		{
			return std::chrono::duration<double>(1.0 / fps);
		}

		// time of one sub-frame
		// you should set fps to display refresh rate
		std::chrono::duration<double> sub_frame_period(double fps) const
		{
			return std::chrono::duration<double>(1.0 / (fps * sub_frame_buffer.max_size));
		}
	};

}