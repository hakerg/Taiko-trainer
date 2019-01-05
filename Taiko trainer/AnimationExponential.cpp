#include "AnimationExponential.h"
#include <cmath>

namespace uc
{

	AnimationExponential::AnimationExponential(double & value_, double factor_, double target_)
		: value(value_), factor(factor_), target(target_)
	{
	}


	AnimationExponential::~AnimationExponential()
	{
	}

	bool AnimationExponential::add_time(std::chrono::duration<double> delta_time)
	{
		value = target + (value - target) * exp(-delta_time.count() * factor);
		return true;
	}

}