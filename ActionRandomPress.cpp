#include "ActionRandomPress.h"


ActionRandomPress::ActionRandomPress(const string& _keyCode, float _lockTimeMin, float _lockTimeMax, 
	float _forceMin, float _forceMax, const initializer_list< pair<Action*, float> >& _initializer)
	:lockTimer(1, true), keyCode(_keyCode), lockTimeMin(_lockTimeMin), lockTimeMax(_lockTimeMax), forceMin(_forceMin), forceMax(_forceMax)
	, Action(_initializer)
{
}

void ActionRandomPress::update(float dt)
{
	owner->press(keyCode, lastForce);
}

bool ActionRandomPress::done()
{
	return lockTimer.isReady();
}

void ActionRandomPress::reset()
{
	lockTimer.time_wait = randRange(lockTimeMin, lockTimeMax);
	lastForce = randRange(forceMin, forceMax);
	
	/*cout << "time_wait " << lockTimer.time_wait << "\n";
	cout << "lastForce " << lastForce << "\n";
	cout << "\n";*/
	lockTimer.restart();
}

