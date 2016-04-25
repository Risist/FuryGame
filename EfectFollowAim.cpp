#include "EfectFollowAim.h"


EfectFollowAim::EfectFollowAim(Game::Object* _aimObject,
	float _movementSpeed, float _movementSpeedIncrease,
	float _decisionRestartTime,
	const Vector2D& _minMaxDistance,
	const Vector2D& _minMaxRotation, bool _rotationAccordingToAim,
	bool _debugInfo)
	: aimObject(_aimObject), movementSpeed(_movementSpeed), timerAim(_decisionRestartTime, true),
	minimalDistance(_minMaxDistance.x), maximalDistance(_minMaxDistance.y),
	minimalRotation(_minMaxRotation.x), maximalRotation(_minMaxRotation.y),
	rotationAccordingToAim(_rotationAccordingToAim), debugInfo(_debugInfo)
{
}


void EfectFollowAim::onUpdate(float dt)
{
	Efect::onUpdate(dt);
	
	if (aimObject == nullptr)
		return;

	Vector2D toToKill = aimObject->getPos().position - getOwner()->getPos().position;
	Vector2D toAim = aim - getOwner()->getPos().position;
	//static float movementSpeed = 0.9;

	getOwner()->onPush(toAim.normalised() * movementSpeed);

	if (timerAim.isReady())
	{
		generateNewAim();
		movementSpeed += movementSpeedIncrease;
		//movementSpeed += 0.0425;
		//movementSpeed *= 1.025;
	}

	/*if (aimObject == nullptr)
		return;

	Vector2D toAim = aim - getPos().position;

	getOwner()->onPush(toAim.normalised() *movementSpeed);

	if (timerAim.isReady())
	{
		aim = aimObject->getPosC().position;
	}*/
}

void EfectFollowAim::generateNewAim()
{
	float distance = randRange(minimalDistance, maximalDistance);
	float rotation = randRange(minimalRotation, maximalRotation);

	if (debugInfo)
	{
		cout << "EfectFollowAim: \n";
		cout << "distance: " << distance << "\n";
		cout << "rotation: " << rotation << "\n";
		cout << "\n";
	}

	if (rotationAccordingToAim)
		rotation += aimObject->getRotC().position;

	Vector2D v(distance);
	v.rotate(rotation);

	aim = aimObject->getPos().position + v;
}