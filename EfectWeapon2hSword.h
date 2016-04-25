#pragma once
#include "EfectWeapon.h"


class EfectWeapon2hSword : public EfectWeapon
{
public:
	EfectWeapon2hSword(sf::Sprite *handSprite = nullptr, sf::Sprite *handSprite2 = nullptr);

	void onInit() override;

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	void wear() override;
	void unwear() override;

	///////////
	EfectDamageOnCollision *efDmg;
	EfectCollisionResponse *efCollision;
	EfectModel * efModel;
	sf::Sprite *handSprite2, middleHand;

	float dmgRatio, pushRatio;
	Vector2D clampDmg, clampPush;


};

