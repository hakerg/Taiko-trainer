#pragma once
#include "TimeDependent.h"

namespace uc
{

	// when time is up, add_time returns false and next calls do nothing
	class TimeLimited :
		public TimeDependent
	{

		virtual bool _add_time(std::chrono::duration<double> delta_time) = 0;

	public:

		std::chrono::duration<double> time_left;

		template <class _Rep, class _Period>
		TimeLimited(std::chrono::duration<_Rep, _Period> time_) :
			time_left(std::chrono::duration_cast<std::chrono::duration<double>>(time_)) {}

		virtual ~TimeLimited();

		// Odziedziczono za poœrednictwem elementu TimeDependent
		bool add_time(std::chrono::duration<double> delta_time) override;
	};

}