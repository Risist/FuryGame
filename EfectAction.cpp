#include "EfectAction.h"


EfectAction::EfectAction(Action* _actualProcessedAction,const initializer_list<Action*> &initializer)
	:actions(initializer), actualProcessedAction(nullptr)
{
	setActualProcessedAction(_actualProcessedAction);
}


EfectAction::~EfectAction()
{
	for each(auto it in actions)
		if (it != nullptr)
			delete it;
}

void EfectAction::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (actualProcessedAction == nullptr)
		return;

	actualProcessedAction->update(dt);

	if (actualProcessedAction->done())
	{
		Action *tryAction = actualProcessedAction->getNextAction();
		//if ( tryAction != actualProcessedAction && tryAction != nullptr)
			//cout << "change action " << tryAction << "\n";
		setActualProcessedAction(tryAction);
	}
}
