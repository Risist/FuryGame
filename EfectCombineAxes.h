#pragma once
#include "GameCompetitor.h"

class EfectCombineAxes : public Game::Efect
{
public:
	EfectCombineAxes(const string& inputCode1 = "", const string& inputCode2 = "", float scaleInput1 = 1, float scaleInput2 = 1);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::Efect::getOwner();
	}

	void onUpdate(float dt) override;

	// 1 - positive value, 2- negative value
	string inputCode1, inputCode2;
	float scaleInput1, scaleInput2;
};

