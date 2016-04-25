#pragma once
#include "EfectWeapon.h"

class EfectWeapon2hAxe : public EfectWeapon
{
public:
	EfectWeapon2hAxe(sf::Sprite* handSprite = nullptr, sf::Sprite* handSprite2 = nullptr);

	void onInit() override;
	void onUpdate(float dt) override;


	EfectDamageOnCollision *efDmg;
	EfectCollisionResponse *efCollision;
	EfectModel * efModel;
	sf::Sprite *handSprite2, middleHand;

};

