#include "EfectAnimation.h"


EfectAnimation::EfectAnimation(const string& _name, const string& _path)
	: state(release), name(_name), path(_path)
{
}

void EfectAnimation::onInit()
{
	Efect::onInit();

	getOwner()->addAnimation(  name, Animation(path));
}

void EfectAnimation::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	switch (state)
	{
	case release:
		if (isPressed)
			state = under;
		break;
	case under:
		if (isPressed)
		{
			auto _state = getAnimation().updateInRange(getOwner()->allModels, getAnimation().getSpeed());
			if (!_state)
			{
				state = awaiting;
			}
		}
		else
			state = returns;
		break;
	case awaiting:
		if (!isPressed)
			state = returns;
		break;
	case returns:
		if (!isPressed)
		{
			auto _state = getAnimation().updateInRange(getOwner()->allModels, -getAnimation().getSpeed());
			if (!_state)
				state = release;

		}
		else
			state = under;
		break;
	}
	

	isPressed = false;
}