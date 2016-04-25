#include "EfectStaticMovement.h"


EfectStaticMovement::EfectStaticMovement( float _movementSpeed)
	: movementSpeed(_movementSpeed)
{
}


void EfectStaticMovement::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	Vector2D v(0, movementSpeed);
	bool pressedAny = false;

	if (getOwner()->isPressed("up"))
	{
		pressedAny = true;

		if (getOwner()->isPressed("left"))
			getOwner()->getRot().position = 0 - 45;
		else if (getOwner()->isPressed("right"))
			getOwner()->getRot().position = 0 + 45;
		else if (!getOwner()->isPressed("down"))
			getOwner()->getRot().position = 0;
		else
			pressedAny = false;
		
	}else
	if (getOwner()->isPressed("down"))
	{
		pressedAny = true;

		if (getOwner()->isPressed("left"))
			getOwner()->getRot().position = 180 + 45;
		else if (getOwner()->isPressed("right"))
			getOwner()->getRot().position = 180 - 45;
		else
			getOwner()->getRot().position = 180;
	}
	else if (getOwner()->isPressed("left") && !getOwner()->isPressed("right"))
	{
		pressedAny = true;
		getOwner()->getRot().position = 270;
	}
	else if (getOwner()->isPressed("right") && !getOwner()->isPressed("left"))
	{
		pressedAny = true;
		getOwner()->getRot().position = 90;
	}

	if ( pressedAny )
	{
		getOwner()->onPush( -v.getRotated(getOwner()->getRot().position));
	}
}