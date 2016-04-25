#include "Action.h"


Action::Action(const initializer_list< pair<Action*, float> >& initializer)
{
	initAfterActions(initializer);
}

void Action::update(float dt)
{
	// does nothing
}
bool Action::done()
{
	// never propage new action
	return false;
}

Action* Action::getNextAction()
{
	Action *bestAction = nullptr;
	float bestEvaluation = 0;

	for (int i = 0; i < afterActions.size(); ++i)
	{
		float evaluation = randRange(0, afterProbablites[i]);
		
		// if actually processed is better than the best till now
		if (evaluation > bestEvaluation)
		{
			// save data of best
			bestEvaluation = evaluation;
			bestAction = afterActions[i];
		}
	}

	return bestAction;
}

void Action::reset()
{

}