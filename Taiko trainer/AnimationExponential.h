#pragma once
#include "TimeDependent.h"

namespace uc
{

	// makes an animation by modifying continuously given external value
	class AnimationExponential : public TimeDependent
	{
	public:

		double factor, target;
		double & value;

		AnimationExponential(double & value_, double factor_, double target_);
		virtual ~AnimationExponential();

		// Odziedziczono za poœrednictwem elementu TimeDependent
		bool add_time(std::chrono::duration<double> delta_time) override;
	};

}