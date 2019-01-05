#pragma once
#include <chrono>
#include <thread>

namespace uc
{

	// calls given function or method periodically in a separate thread
	// makes sure that calling frequency is constant - when one call takes too much time object will make next calls more often
	// you can change period and next_call_time at any time
	class LoopedThread
	{

		std::thread _thread;

	public:

		bool running;
		std::chrono::nanoseconds period;
		std::chrono::high_resolution_clock::time_point next_call_time;

		// function_to_loop_: return false if thread has to be killed. Should not be looped
		template <class _Rep, class _Period, class... _Args>
		LoopedThread(
			std::chrono::duration<_Rep, _Period> period_,
			bool wait_until_first_execution_,
			bool(*function_to_loop_)(_Args...),
			_Args&&... args_)
			:
			period(std::chrono::duration_cast<std::chrono::nanoseconds>(period_)),
			running(true)
		{

			if (wait_until_first_execution_) next_call_time = std::chrono::high_resolution_clock::now() + period;
			else next_call_time = std::chrono::high_resolution_clock::now();

			_thread = std::thread(
				&LoopedThread::loop_function_periodically<_Args...>,
				this,
				function_to_loop_,
				args_...);
		}

		// method_to_loop_: return false if thread has to be killed. Should not be looped
		template <class _Rep, class _Period, class _Class, class... _Args>
		LoopedThread(
			std::chrono::duration<_Rep, _Period> period_,
			bool wait_until_first_execution_,
			_Class* object_,
			bool(_Class::*method_to_loop_)(_Args...),
			_Args&&... args_)
			:
			period(std::chrono::duration_cast<std::chrono::nanoseconds>(period_)),
			running(true)
		{

			if (wait_until_first_execution_) next_call_time = std::chrono::high_resolution_clock::now() + period;
			else next_call_time = std::chrono::high_resolution_clock::now();

			_thread = std::thread(
				&LoopedThread::loop_method_periodically<_Class, _Args...>,
				this,
				object_,
				method_to_loop_,
				args_...);
		}

		virtual ~LoopedThread();

		void request_stop();
		void stop();

		void wait_until_finished();


		template <class... _Args>
		void loop_function_periodically(bool(*function_to_loop)(_Args...), _Args&&... args)
		{

			while (running)
			{

				if (std::chrono::high_resolution_clock::now() < next_call_time - std::chrono::nanoseconds(2000000))
				{

					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					continue;

				}
				if (std::chrono::high_resolution_clock::now() < next_call_time)
				{

					std::this_thread::yield();
					continue;

				}

				if (!function_to_loop(args...))
				{
					running = false;
					return;
				}

				next_call_time += period;

			}
		}

		template <class _Class, class... _Args>
		void loop_method_periodically(_Class* object, bool(_Class::*method_to_loop)(_Args...), _Args&&... args)
		{

			while (running)
			{

				if (std::chrono::high_resolution_clock::now() < next_call_time - std::chrono::nanoseconds(2000000))
				{

					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					continue;

				}
				if (std::chrono::high_resolution_clock::now() < next_call_time)
				{

					std::this_thread::yield();
					continue;

				}

				if (!(object->*method_to_loop)(args...))
				{
					running = false;
					return;
				}

				next_call_time += period;

			}
		}

	};

}