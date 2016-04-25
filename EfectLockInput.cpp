#include "EfectLockInput.h"


EfectLockInput::EfectLockInput(const string& _inputCode, float _lockTime)
	: inputCode(_inputCode), lockTimer(_lockTime)
{
}


void EfectLockInput::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (lockTimer.isReady())
	{
		lastValue = getOwner()->keys[inputCode];

	}else
		getOwner()->keys[inputCode] = lastValue;
}
