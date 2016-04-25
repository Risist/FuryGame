#include "ActionRandomDrag.h"


ActionRandomDrag::ActionRandomDrag(float *_resource, float _forceMin, float _forceMax
	, float _lockTimeMin, float _lockTimeMax, const initializer_list< pair<Action*, float> >& _initializer)
	: resource(_resource), forceMin(_forceMin), forceMax(_forceMax), lockTimeMin(_lockTimeMin), lockTimeMax(_lockTimeMax),
	Action(_initializer)
{
}


void ActionRandomDrag::update(float dt)
{
	if (resource != nullptr)
		(*resource) += lastForce;
}
bool ActionRandomDrag::done()
{
	return lockTimer.isReady();
}

void ActionRandomDrag::reset()
{
	lockTimer.time_wait = randRange(lockTimeMin, lockTimeMax);
	lastForce = randRange(forceMin, forceMax);
	lockTimer.restart();
}
