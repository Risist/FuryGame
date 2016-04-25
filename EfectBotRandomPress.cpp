#include "EfectBotRandomPress.h"

EfectBotRandomPress::EfectBotRandomPress(string _code, float _timeMin, float _timeMax, float _probablity)
	: code(_code), timeMin(_timeMin), timeMax(_timeMax), probablity(_probablity)
{

}

void EfectBotRandomPress::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (timer.isReady())
	{
		timer.restart();
		timer.time_wait = randRange(timeMin, timeMax);
		state = (randRange(0, 1) < probablity);
	}

	if (state == true)
		getOwner()->press(code);
}
