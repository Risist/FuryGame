#pragma once
#include "GameWorld.h"
#include "GamePlayer.h"
#include "efects.h"
#include "EfectWeapon.h"
#include "EfectBodyWarrior.h"

namespace El
{
	class Player : public Game::Player
	{
	public:
		Player();

		void onInit() override;
		void onDisplay(Camera& cam) override;
		void onUpdate(float dt) override;
		bool onDeath() override;

		EfectWeapon *efWeaponLeft, *efWeaponRight;
		EfectBodyWarrior *efBodyWarrior;


		float score;
	};

}

