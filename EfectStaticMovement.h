#pragma once
#include "GameWorld.h"
#include "GameCompetitor.h"

class EfectStaticMovement : public Game::Efect
{
public:
	EfectStaticMovement( float _movementSpeed = 0);

	void onUpdate(float dt) override;

	Game::Competitor*  getOwner()
	{
		return (Game::Competitor*)Game::Efect::getOwner();
	}

	float movementSpeed;
};

