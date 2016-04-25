#pragma once
#include "GameObject.h"

namespace Allow
{
	class Base
	{
	public:
		Base(bool _negation = false)
			: negation(_negation)
		{
		}
		virtual ~Base(){}

		virtual bool allow(Game::Object* obj){ return getWithNegation(false); };

		bool getWithNegation(bool b)
		{
			if (negation)
				return !b;
			else
				return b;
		}

		bool negation;
	};

}

