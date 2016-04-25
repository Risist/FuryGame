#include "EfectTppMovement.h"


EfectTppMovement::EfectTppMovement(float _movementSpeed, float _rotationSpeed) 
	: movementSpeed(_movementSpeed), rotationSpeed(_rotationSpeed)
{
}

void EfectTppMovement::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);
}

void EfectTppMovement::onUpdate( float dt)
{
	Efect::onUpdate(dt);

	getOwner()->onSwing(getOwner()->getDrag().x * rotationSpeed);


	if (!(getOwner()->isPressed("up") && getOwner()->isPressed("down")))
	{
		if (getOwner()->isPressed("up"))
		{
			Vector2D v(0, -movementSpeed*dt);
			v.rotate(getOwner()->getRotC().position);

			if (!(getOwner()->isPressed("left") && getOwner()->isPressed("right")))
			{
				if (getOwner()->isPressed("left"))
				{
					v.rotate(-45);
				}
				else if (getOwner()->isPressed("right"))
				{
					v.rotate(45);
				}
			}

			getOwner()->onPush(v);
		}
		if (getOwner()->isPressed("down"))
		{
			Vector2D v(0, movementSpeed);
			v.rotate(getOwner()->getRotC().position);

			if (!(getOwner()->isPressed("left") && getOwner()->isPressed("right")))
			{
				if (getOwner()->isPressed("left"))
				{
					v.rotate(45);
				}
				else if ( getOwner()->isPressed("right"))
				{
					v.rotate(-45);
				}
			}

			getOwner()->onPush(v);
		}
	}
	if (!(getOwner()->isPressed("left") && getOwner()->isPressed("right")) && !getOwner()->isPressed("up") && !getOwner()->isPressed("down"))
	{
		if (getOwner()->isPressed("left"))
		{
			Vector2D v(-movementSpeed, 0);
			v.rotate(getOwner()->getRotC().position);
			getOwner()->onPush(v);
		}
		else if (getOwner()->isPressed("right"))
		{
			Vector2D v(movementSpeed, 0);
			v.rotate(getOwner()->getRotC().position);
			getOwner()->onPush(v);
		}
	}
}
