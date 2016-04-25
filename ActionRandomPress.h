#pragma once
#include "Action.h"
#include "control.h"

class ActionRandomPress : public Action
{
public:
	ActionRandomPress(const string& keyCode = "", float lockTimeMin = 0.1, float lockTimeMax = 0.5, float forceMin = 1, float forceMax = 1, const initializer_list< pair<Action*, float> >& initializer = {});

	void update(float dt) override;
	bool done() override;
	void reset() override;

	// code of key to press
	string keyCode;

	float lastForce, forceMin, forceMax;
	Control::Timer lockTimer;
	float lockTimeMin, lockTimeMax;
};

