#include "EfectWeapon.h"


EfectWeapon::EfectWeapon( sf::Sprite* _handSprite, const string& _animCodeX, const string& _animCodeY)
	:handSprite(_handSprite), animCodeX(_animCodeX), animCodeY(_animCodeY), strenghtX(1), strenghtY(1)
{
}


void EfectWeapon::onInit()
{
	Game::MultiEfectNoInteract::onInit();

	// addResource
	idResX = getOwner()->addResource( Resource<float>() );
	getResX().resetVelocity = 0.7;
	getResX().inverseMass = -1.f;
	
	idResY = getOwner()->addResource(Resource<float>());
	getResY().resetVelocity = 0.7;
	getResY().inverseMass = -1.f;
}

void EfectWeapon::onUpdate(float dt)
{
	Game::MultiEfectNoInteract::onUpdate(dt);

	if (pressed)
	{
		getResX().addForce(getOwner()->getDrag().x * strenghtX);
		getResY().addForce(getOwner()->getDrag().y * strenghtY);
	}

	getOwner()->getAnimation(animCodeX).updateInRange(getOwner()->allModels, getResX().velocity);
	getOwner()->getAnimation(animCodeY).updateInRange(getOwner()->allModels, getResY().velocity);

	pressed = false;
}