#include "ControlTimer.h"


namespace Control
{
	sf::Clock Timer::clock;

	Timer::Timer(float _time_wait, bool _restart, float _time_add, float _time_init)
		: time_wait(_time_wait), restart_on_ready(_restart), time_add(_time_add), last_time(_time_init)
	{

	}

	bool Timer::isReady()
	{
		if (getTimeDiffirence() >= time_wait)
		{
			if (restart_on_ready)
				restart();
			time_wait += time_add;

			return true;
		}
		return false;
	}

	bool Timer::isReadyCheck()
	{
		if (getTimeDiffirence() >= time_wait)
			return true;
		return false;
	}
	bool Timer::isReady(float time)
	{
		if (getTimeDiffirence() >= time)
			return true;
		return false;
	}
	bool Timer::isReadyRestart(float time)
	{
		if (getTimeDiffirence() >= time)
		{
			restart();
			return true;
		}
		return false;
	}

}