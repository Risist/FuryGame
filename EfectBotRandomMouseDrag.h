#pragma once
#include "GameCompetitor.h"
#include "control.h"

/*
Owner should inherit from Competitor class

*/
class EfectBotRandomMouseDrag : public Game::Efect
{
public:
	EfectBotRandomMouseDrag(float *v = nullptr, float forceMin = -7.5, float forceMax =7.5, float timeMin = 0.1, float timeMax= 0.3);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}

	void onUpdate(float dt) override;

	Control::Timer timer;
	float timeMin, timeMax;

	float lastForce;
	float forceMin, forceMax;

	float *v;
};

