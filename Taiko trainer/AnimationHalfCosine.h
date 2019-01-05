#pragma once
#include "math_defines.h"
#include "TimeLimited.h"

namespace uc
{

	class AnimationHalfCosine :
		public TimeLimited
	{

		// Odziedziczono za poœrednictwem elementu TimeLimited
		bool _add_time(std::chrono::duration<double> delta_time) override;

	public:

		double middle, amplitude, speed_rad_per_second;
		double & value;

		template <class _Rep, class _Period>
		AnimationHalfCosine(double & value_, double target_offset_, std::chrono::duration<_Rep, _Period> time_) :
			value(value_),
			middle(value_ + target_offset_ * 0.5),
			amplitude(target_offset_ * 0.5),
			speed_rad_per_second(PI / std::chrono::duration_cast<std::chrono::duration<double>>(time_).count()),
			TimeLimited(std::chrono::duration_cast<std::chrono::duration<double>>(time_)) {}

		virtual ~AnimationHalfCosine();
	};

}