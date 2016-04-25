#pragma once
#include "allow.h"
#include "GameEfect.h"

class EfectUseUnderCondition : public Game::Efect
{
public:
	EfectUseUnderCondition(Game::Efect* _ef = nullptr, Allow::Base* _condition = nullptr)
		: ef(_ef), condition(_condition)
	{

	}
	~EfectUseUnderCondition()
	{
		if (condition != nullptr)
			delete condition;
	}

	Game::Efect *ef;
	Allow::Base *condition; // new ; delete


	void onUpdate(float dt) override
	{
		Game::Efect::onUpdate(dt);
		if (ef == nullptr || condition == nullptr)
			return;
		ef->activated = condition->allow(getOwner());
	}


};

