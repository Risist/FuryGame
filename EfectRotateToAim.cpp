#include "EfectRotateToAim.h"


EfectRotateToAim::EfectRotateToAim(Game::Object*_aim, float _force, float _minDiff)
	: aim(_aim), force(_force), minDiff(_minDiff)
{
}

void EfectRotateToAim::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (aim == nullptr)
		return;

	auto toAim = getOwner()->getPosC().position - aim->getPosC().position;
	float toAimRotation = toAim.angle();
	float myRotation = getOwner()->getRotC().position;

	float angleDiff = minimalAngleDiffirence(toAimRotation, myRotation);
	float direction = angleDiff > 0 ? 1.f : -1.f;
	
	//cout << "angleDiff = " << angleDiff << "\n";
	//cout << "direction = " << direction << "\n";
	//system("cls");
	if ( angleDiff * angleDiff > minDiff * minDiff)
		getOwner()->onSwing(force *direction);
}

