#pragma once
#include "GameCompetitor.h"
#include <initializer_list>

class Action
{
public:
	Action(const initializer_list< pair<Action*, float> >& initializer = {});

	void initAfterActions( const initializer_list< pair<Action*, float> >& initializer )
	{
		for each(auto it in initializer)
		{
			afterActions.push_back(it.first);
			afterProbablites.push_back(it.second);
		}
	}

	// this event should tell what will hapened if the bot will use the action 
	virtual void update(float dt);

	// this event tells whether or not action is ended up
	// if yes then will be choosen next action from list
	virtual bool done();

	// when this action is chosen to execute 
	// there could be need of reset some propertites
	virtual void reset();

	virtual Action* getNextAction();


	virtual void setOwner( Game::Competitor* s)
	{
		owner = s;
	}
	// competitor who the action will take control on
	Game::Competitor *owner;

	void addAfterAction(Action* action, float probablity)
	{
		afterActions.push_back(action);
		afterProbablites.push_back(probablity);
	}

	// both after actions and probablites sets have equal size
	// first one represents action that is possible to be next executed after this one
	// secound tels how big is probablity to occur it
	// probablity should be an positive value
	vector<Action*> afterActions;
	vector<float> afterProbablites;
};

