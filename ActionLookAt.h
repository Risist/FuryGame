#pragma once
#include "Action.h"

class ActionLookAt : public Action
{
public:
	ActionLookAt(Game::Object **aim = nullptr, float timeDiference = 0, float forceRatio = 1, float maxForce = 7.5, float tolerance = 10, const initializer_list< pair<Action*, float> >& initializer = {});

	void update(float dt) override;
	bool done() override;


	// if diference in angle is less than tolerance algorithm is done
	float tolerance;

	// defines how force is applied to the owner
	float forceRatio, maxForce;

	// position of the aim will be tried to predict 
	// after time diference
	float timeDiference;

	// a pointner to adress of aim
	// the owner will try to look at the aim
	Game::Object **aim;

private:
	bool isDone;
};

