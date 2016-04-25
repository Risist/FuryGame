#pragma once
#include "GameWorld.h"
#include "control.h"
#include "GameCompetitor.h"
#include "GameProjectile.h"

class EfectSkill : public Game::Efect
{
public:
	EfectSkill( const Control::Timer& timer = Control::Timer(), const string& inputName = "");

	// owner must be an Competitor
	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}

	void addProjectile(Game::Projectile* projectile);

	Control::Timer timer;
	string inputName;
};

