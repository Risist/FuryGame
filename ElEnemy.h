#pragma once
#include "EfectBodyWarrior.h"
#include "ElPlayer.h"
#include "actions.h"

namespace El
{

	class Enemy : public Game::Competitor
	{
	public:
		Enemy(size_t idWeapon = 0, El::Player *player = nullptr);

		void onInit() override;
		void addStates();

		void onUpdate( float dt) override;
		bool onDeath() override;

		void findAim();
		Control::Timer tNewAim;

		Evaluate::Operator evaluate;
		Game::Object *aim;
		vector<Game::Object*> aimsToAvoid;
		ActionMoveTo *stayOnTheMap;

		size_t idWeapon;
		bool alive;

		EfectBodyWarrior *efBodyWarrior;
		El::Player *player;
		Control::Timer deathTimer;
	};

}