#pragma once
#include <chrono>

namespace uc
{

	class TimeDependent
	{
	public:
		TimeDependent();
		virtual ~TimeDependent();

		// return true if success, false if animation finished
		virtual bool add_time(std::chrono::duration<double> delta_time) = 0;
	};

}