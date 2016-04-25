#include "ActionLookAt.h"


ActionLookAt::ActionLookAt(Game::Object **_aim, float _timeDiference, float _forceRatio, float _maxForce, float _tolerance, const initializer_list< pair<Action*, float> >& _initializer)
	: aim(_aim), timeDiference(_timeDiference), forceRatio(_forceRatio), maxForce(_maxForce), tolerance(_tolerance), Action(_initializer)
{
}

void ActionLookAt::update(float dt)
{
	if (*aim != nullptr)
		isDone = owner->lookAt( *aim, timeDiference, forceRatio, maxForce, tolerance);
}

bool ActionLookAt::done()
{
	return isDone;
}
