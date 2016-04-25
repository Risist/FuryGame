#pragma once
#include "Action.h"

class EfectAction : public Game::Efect
{
public:
	EfectAction(Action* actualProcessedAction = nullptr, const initializer_list<Action*> &initializer = {});
	~EfectAction();

	void initActions(const initializer_list<Action*>& initializer)
	{
		actions = initializer;
		for each(auto it in actions)
			if (it != nullptr)
				it->setOwner( (Game::Competitor*)getOwner() );
	}

	void onUpdate(float dt) override;

	void setActualProcessedAction(Action *toSet)
	{
		if (toSet != nullptr)
			actualProcessedAction = toSet;

		if (actualProcessedAction != nullptr)
			actualProcessedAction->reset();
	}


	vector<Action*> actions;
	Action *actualProcessedAction;
};

