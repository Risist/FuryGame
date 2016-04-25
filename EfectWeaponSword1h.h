#pragma once
#include "EfectWeapon.h"


class EfectWeaponSword1h : public EfectWeapon
{
public:
	EfectWeaponSword1h( sf::Sprite* handSprite = nullptr);

	void onInit() override;

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	void wear() override;
	void unwear() override;

	EfectModel * efModel;

	///////////
	EfectDamageOnCollision *efDmg;
	EfectCollisionResponse *efCollision;

	float dmgRatio, pushRatio;
	Vector2D clampDmg, clampPush;

	float changeRotation;

};

