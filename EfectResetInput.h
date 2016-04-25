#pragma once
#include "GameCompetitor.h"

class EfectResetInput : public Game::Competitor
{
public:
	EfectResetInput(){}

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}
	void onUpdate(float dt)
	{
		getOwner()->resetInput();
	}


};

