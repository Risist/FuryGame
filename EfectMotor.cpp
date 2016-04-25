#include "EfectMotor.h"


EfectMotor::EfectMotor(const Vector2D& _force, bool _accordingToOwner, bool _trueForce)
	: force(_force), accordingToOwner(_accordingToOwner), trueForce(_trueForce)
{
}


void EfectMotor::onUpdate(float dt)
{
	Efect::onUpdate(dt);
	Vector2D _force = force;
	if (accordingToOwner)
		_force.rotate(getOwner()->getRotC().position);

	if (trueForce)
		getOwner()->getPos().velocity += _force;
	else
		getOwner()->onPush(_force);
}