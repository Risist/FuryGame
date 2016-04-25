#include "EfectSpringJoint.h"
#include "GameObject.h"

EfectSpringJoint::EfectSpringJoint(Game::Object *_myObject, Game::Object *_otherObject, float _forceRatio, 
	sf::Sprite *_myConnectedTo, sf::Sprite *_otherConnectedTo, const Vector2D& _myAnchor, const Vector2D& _otherAnchor)
	: myToAffect(_myObject), otherToAffect(_otherObject), forceRatio(_forceRatio), 
	myConnectedTo(_myConnectedTo), otherConnectedTo(_otherConnectedTo),
	myAnchor(_myAnchor), otherAnchor(_otherAnchor)
{
}

void EfectSpringJoint::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	Vector2D myPosition = myAnchor, 
		otherPosition = otherAnchor;

	if (myConnectedTo != nullptr)
	{
		myPosition.rotate(myConnectedTo->getRotation());
		myPosition *= myConnectedTo->getScale();
		myPosition += myConnectedTo->getPosition();
	}
	if (otherConnectedTo != nullptr)
	{
		otherPosition.rotate(otherConnectedTo->getRotation());
		otherPosition *= otherConnectedTo->getScale();
		otherPosition += otherConnectedTo->getPosition();
	}

	Vector2D toOther = myPosition-otherPosition;


	myToAffect->onPush( toOther * forceRatio);
}
