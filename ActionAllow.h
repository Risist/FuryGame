#pragma once
#include "Action.h"
#include "allow.h"

class ActionAllow : public Action
{
public:
	ActionAllow(Allow::Base *_allow = nullptr, const initializer_list< pair<Action*, float> >& initializer = {})
		: allow(_allow), Action(initializer)
	{

	}
	~ActionAllow()
	{
		if (allow != nullptr)
			delete allow;
	}

	bool done() override
	{ 
		if (allow != nullptr)
			return allow->allow(owner);
		else
			return Action::done();
	}

	Allow::Base *allow;
};

