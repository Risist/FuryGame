#pragma once
#include "Action.h"


class ActionSet : public Action
{
public:
	ActionSet(const initializer_list<Action*> &initializer = {} );
	~ActionSet();

	void initAfterActions(const initializer_list<Action*> &initializer)
	{
		afterActions = initializer;
	}

	void setOwner( Game::Competitor * s) override;

	// run script for each element
	void update(float dt) override;

	// check whether one of elements is done
	bool done() override;

	// will return chosen action of first done element
	Action* getNextAction() override;

	// reset all actions
	void reset() override;


	// 
	Action *chosenAction;

	// this class will reuse set mentioned below
	// the reason is that it has no sense it this context 
	// but there still is need for an Actions container
	// the container will store list of Actions under control of this one
	//vector<Action*> afterActions

private:
	// it must be locked; i did so big mistake because of this
	// ill not let anyone to repeat that
	using Action::addAfterAction;
};

