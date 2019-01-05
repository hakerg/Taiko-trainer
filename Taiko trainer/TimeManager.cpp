#include "TimeManager.h"

namespace uc
{

	TimeManager::TimeManager()
	{
	}


	TimeManager::~TimeManager()
	{
	}

	bool TimeManager::add_time(std::chrono::duration<double> delta_time)
	{
		for (auto it = begin(); it != end();)
		{
			if ((*it)->add_time(delta_time))
			{
				it++;
			}
			else
			{
				auto it_to_remove = it;
				it++;
				erase(it_to_remove);
			}
		}
		return true;
	}

}