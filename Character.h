#pragma once
#include "GamePlayer.h"
#include "ParticleGenerator.h"

class Character : public Game::Player
{
public:
	Character();

	void onInit() override;

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	void onCollision(Game::Object* other, const pair<int, int >& firstColliderId) override;
	void movementScript(float movementSpeed);

	enum WeaponState
	{
		release,
		under,
		awaiting,
		returns,

	}shieldState, swordState;
	void shieldScript();
	void swordScript();

	size_t idAnimAtU, idAnimAtH;
	ParticleGenerator gen, genSword;
};

