#pragma once
#include "efects.h"
#include "GameCompetitor.h"

class EfectWeaponAxe1h : public Game::Efect
{
public:
	EfectWeaponAxe1h(sf::Sprite* handSprite = nullptr);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*)Game::Efect::getOwner();
	}

	void onInit() override;

	void onUpdate(float dt) override;

	EfectModel * efModel;
	sf::Sprite *handSprite;

	Resource<float>& getResX()
	{
		return getOwner()->getResource_f(idResX);
	}
	Resource<float>& getResY()
	{
		return getOwner()->getResource_f(idResY);
	}
	size_t idResX, idResY;

	///////////
	EfectDamageOnCollision *efDmg;
	EfectCollisionResponse *efCollision;

	float dmgRatio, pushRatio;
	Vector2D clampDmg, clampPush;

	float changeRotation;

};

