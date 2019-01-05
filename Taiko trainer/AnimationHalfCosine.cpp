#include "AnimationHalfCosine.h"

namespace uc
{

	AnimationHalfCosine::~AnimationHalfCosine()
	{
	}

	bool AnimationHalfCosine::_add_time(std::chrono::duration<double> delta_time)
	{

		value = middle + amplitude * cos(time_left.count() * speed_rad_per_second);

		return true;
	}

}