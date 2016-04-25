#pragma once
#include "EfectWeapon.h"

class EfectWeaponMagic : public EfectWeapon
{
public:
	EfectWeaponMagic(sf::Sprite *handSprite = nullptr, sf::Sprite *handSprite2 = nullptr);

	void onInit() override;
	void onUpdate( float dt) override;

	sf::Sprite *handSprite2, middleHand;
};

