#include "EfectJumpMovement.h"


EfectJumpMovement::EfectJumpMovement(float speed, const string& _jumpKeyCode, size_t _resid, float _minimalCd, float _scaleCd, float jumpTime, float _cost)
	:EfectTppMovement(speed, 0), jumpKeyCode(_jumpKeyCode), jumpCd(_minimalCd), scaleCd(_scaleCd), timerJump(jumpTime), state(false), resId(_resid), cost(_cost)
{
}

void EfectJumpMovement::onInit()
{
	Game::Efect::onInit();
}

void EfectJumpMovement::onUpdate(float dt)
{
	if (state == false)
	{
		if (getOwner()->isPressed(jumpKeyCode) && jumpCd.isReady())
		{
			getRes().addForce(cost);
			state = true;
			timerJump.restart();
		}
	}
	else
	{
		EfectTppMovement::onUpdate(dt);
		if (timerJump.isReady())
			state = false;
	}

	jumpCd.time_wait = minimalCd + getRes().velocity * scaleCd;
	//cout << jumpCd.time_wait << "\n";
	//cout << getRes().velocity << "\n";
}
