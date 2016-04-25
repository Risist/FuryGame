#pragma once
#include "ElDummy.h"

namespace El
{
	class RotatingDummy : public Game::Object
	{
	public:
		RotatingDummy(Game::Object *toFollow = nullptr);

		void onInit() override;
		void onUpdate(float dt) override;
		void onDisplay(Camera& cam) override;

		// respawn
		void onInteract(float force, size_t resId, Game::Object* causer) override;
		bool onDeath() override;
		Control::Timer respawnTimer;
		Vector2D lockedPosition;

		EfectModel *efModel;
		Game::Object *toFollow;
	};

}

