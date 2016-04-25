#pragma once
#include "Action.h"
#include "control.h"

class ActionRandomDrag : public Action
{
public:
	ActionRandomDrag(float *resource = nullptr, float forceMin = -7.5, float forceMax = 7.5, float lockTimeMin = 0.1, float lockTimeMax = 0.3,
		const initializer_list< pair<Action*, float> >& initializer = {});

	void update(float dt) override;
	bool done() override;
	void reset() override;

	float lastForce, forceMin, forceMax;
	Control::Timer lockTimer;
	float lockTimeMin, lockTimeMax;

	float *resource;

};

