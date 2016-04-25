#pragma once
#include "GameProjectile.h"

class Bullet : public Game::Projectile
{
public:
	Bullet(Game::Object *owner = nullptr);

	void onInit() override;

	void onUpdate(float dt) override;

	void onCollision(Game::Object* other, const pair<int, int >& firstColliderId) override;
};

