#include "EvaluateTimer.h"

namespace Evaluate
{
	float Timer::evaluate(Game::Object *obj)
	{
		if (timer == nullptr)
		{
			cout << "timer in evaluate class equal to nullptr\n";
			return 0;
		}

		float r = 0;
	
		if( mode == actualTime )
			r = timer->getTimeDiffirence();
		else if ( mode == cd)
			r = timer->time_wait;

		return r;

	}

}