#include "EfectParticle.h"


EfectParticle::EfectParticle(const string& pathParticle, size_t nParticle, float offsetParticle, float _animationSpeed, float begginsFrom, Sprite* _connectedToUpdate, Sprite* _connectedToDisplay)
	: connectedToUpdate(_connectedToUpdate), connectedToDisplay(_connectedToDisplay), animationSpeed(_animationSpeed)
{
	gen.addParticle(pathParticle, nParticle, offsetParticle, begginsFrom);
}

void EfectParticle::onInit()
{
	Efect::onInit();
}

void EfectParticle::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (connectedToUpdate == nullptr)
		gen.update(dt*animationSpeed);
	else
		gen.update(dt*animationSpeed, *connectedToUpdate);
}
void EfectParticle::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);

	if (connectedToDisplay == nullptr)
		gen.display(cam);
	else
		gen.display(cam, *connectedToDisplay);
}