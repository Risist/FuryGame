#include "ActionSet.h"


ActionSet::ActionSet(const initializer_list<Action*> &initializer)
{
	initAfterActions(initializer);
}
ActionSet::~ActionSet()
{
	for each(auto it in afterActions)
		if (it != nullptr)
			delete it;
}

void ActionSet::update(float dt)
{
	for each(auto it in afterActions)
		if ( it != this && it != nullptr)
			it->update(dt);
}

bool ActionSet::done()
{
	for each(auto it in afterActions)
		if (it != this && it != nullptr && it->done())
		{
			auto tryAction = it->getNextAction();

			if (tryAction != nullptr)
			{
				chosenAction = tryAction;
				return true;
			}
		}

	return false;
}

Action* ActionSet::getNextAction()
{
	auto returnedValue = chosenAction;
	chosenAction = nullptr;
	return returnedValue;
	//return Action::getNextAction();
}

// reset all actions
void ActionSet::reset()
{
	for each(auto it in afterActions)
		if ( it != this && it != nullptr)
			it->reset();
}

void ActionSet::setOwner(Game::Competitor * s)
{
	for each (auto it in afterActions)
		if ( it != this && it != nullptr )
			it->setOwner(s);
}
