#include "EfectBotRandomMouseDrag.h"


EfectBotRandomMouseDrag::EfectBotRandomMouseDrag( float *_v, float _forceMin, float _forceMax, float _timeMin, float _timeMax)
	: v(_v), forceMin(_forceMin), forceMax(_forceMax), timeMin(_timeMin), timeMax(_timeMax)
{
}

void EfectBotRandomMouseDrag::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (timer.isReady())
	{
		lastForce = randRange( forceMin, forceMax);
		timer.time_wait = randRange(timeMin, timeMax);
		timer.restart();
	}

	if (v != nullptr)
		(*v) += lastForce;
}
