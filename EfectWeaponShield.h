#pragma once
#include "EfectWeapon.h"

class EfectWeaponShield : public EfectWeapon
{
public:
	EfectWeaponShield( sf::Sprite* handSprite = nullptr);

	void onInit() override;
	void onUpdate(float dt) override;

	EfectModel *efModel;
};

