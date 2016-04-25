#pragma once
#include "AllowBase.h"
#include "control.h"

namespace Allow
{
	class Timer : public Base
	{
	public:
		Timer(const Control::Timer& _timer = Control::Timer() )
			: timer(_timer)
		{

		}
		
		bool allow(Game::Object *obj)
		{
			return getWithNegation(timer.isReady());
		}

		Control::Timer timer;
	};

}

