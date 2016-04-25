#pragma once
#include "GameObject.h"

class EfectDamageOnCollision : public Game::Efect
{
public:
	EfectDamageOnCollision(float flatDamage = 0, float springDamage = 0,float maxSpring = 999999);

	void onCollision(const ColliderInfo& otherCollider) override;

	float flatDamage, springDamage, maxSpring;
};

