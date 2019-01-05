#include "TimeLimited.h"

namespace uc
{

	TimeLimited::~TimeLimited()
	{
	}

	bool TimeLimited::add_time(std::chrono::duration<double> delta_time)
	{
		if (delta_time > time_left) delta_time = time_left;

		bool ret = _add_time(delta_time);
		time_left -= delta_time;

		return ret && time_left > std::chrono::duration<double>::zero();
	}

}