#pragma once
#include "GameCompetitor.h"
#include "control.h"

/*
Owner should inherit from Competitor class

*/
class EfectBotRandomPress : public Game::Efect
{
public:
	EfectBotRandomPress(string code = "", float timeMin = 0.1, float timeMax = 0.3, float probablity = 0.5);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}

	void onUpdate(float dt) override;

	Control::Timer timer;
	float timeMin, timeMax;
	string code;
	bool state;

	// should be in range of 0 to 1
	// if randomized value form above partition is bigger than probablity
	// code is pressed otherwise unpressed
	float probablity;

};

