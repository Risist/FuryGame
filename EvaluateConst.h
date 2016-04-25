#pragma once
#include "EvaluateBase.h"

namespace Evaluate
{
	class Const : public Base
	{
	public:

		Const( float _value = 0)
			: value(_value)
		{
		}

		float evaluate(Game::Object* obj) override
		{ 
			return value;
		}


		float value;

	};

}

