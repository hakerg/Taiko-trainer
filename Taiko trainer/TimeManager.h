#pragma once
#include <list>
#include <memory>
#include "TimeDependent.h"

namespace uc
{

	// keeps all TimeDependent objects in one place
	class TimeManager :
		public TimeDependent, public std::list<std::shared_ptr<TimeDependent>>
	{
	public:

		TimeManager();
		virtual ~TimeManager();

		// Odziedziczono za poœrednictwem elementu TimeDependent
		bool add_time(std::chrono::duration<double> delta_time) override;
	};

}