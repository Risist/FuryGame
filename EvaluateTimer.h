#pragma once
#include "EvaluateBase.h"
#include "control.h"

namespace Evaluate
{
	class Timer : public Base
	{
	public:
		enum Mode
		{
			actualTime,
			cd
		}mode;

		Timer(Control::Timer* _timer, Mode _mode = actualTime)
			: timer(_timer), mode(_mode)
		{

		}

		float evaluate(Game::Object *obj) override;

		Control::Timer *timer;
	};

}

