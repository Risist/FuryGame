#include "EfectCheckForCollision.h"


EfectCheckForCollision::EfectCheckForCollision(vector<Game::Object*> *_world)
	: world(_world)
{
}


void EfectCheckForCollision::onInit()
{
	Efect::onInit();
	getOwner()->isCheckingForCollision = true;
}
void EfectCheckForCollision::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (world == nullptr)
		return;

	getOwner()->checkForCollision(*world);
}
