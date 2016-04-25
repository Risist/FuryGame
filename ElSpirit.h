#pragma once
#include "GameWorld.h"
#include "efects.h"

namespace El
{

	class Spirit : public Game::Object
	{
	public:
		Spirit();

		void onInit() override;

		void onUpdate(float dt) override;
		void onDisplay(Camera& cam) override;
		bool onDeath() override
		{
			return false;
		}

		EfectModel *efModel;
		EfectFollowAim *efFollowAim;
		EfectDamageOnCollision *efDamageOnCollision;

		void findAim();

		Control::Timer tNewAim;
	};

}

