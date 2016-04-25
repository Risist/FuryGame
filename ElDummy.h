#pragma once
#include "GameWorld.h"
#include "efects.h"
#include "control.h"

namespace El
{
	class Dummy : public Game::Object
	{
	public:
		Dummy();

		void onInit() override;
		void onUpdate(float dt) override;
		void onDisplay(Camera& cam) override;

		// respawn
		void onInteract(float force, size_t resId, Game::Object* causer) override;
		bool onDeath() override;
		Control::Timer respawnTimer;
		Vector2D lockedPosition;

		EfectModel *efModel;
		bool alive;
		Control::Timer deathTimer;
	};

}

