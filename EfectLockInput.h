#pragma once
#include "GameCompetitor.h"
#include "control.h"

class EfectLockInput : public Game::Efect
{
public:
	EfectLockInput( const string& inputCode = "", float lockTime = 1);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}

	void onUpdate(float dt) override;

	string inputCode;
	float lastValue;
	Control::Timer lockTimer;
};

