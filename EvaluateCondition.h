#pragma once
#include "EvaluateBase.h"
#include "AllowBase.h"


namespace Evaluate
{
	class Condition : public Base
	{
	public:

		Condition( Base* _valueTrue = nullptr, Base* _valueFalse = nullptr, Allow::Base* _condition = nullptr)
			: valueTrue(_valueTrue), valueFalse(_valueFalse), condition(_condition)
		{
		}

		~Condition()
		{
			if (condition != nullptr)
				delete condition;
			if (valueTrue != nullptr)
				delete valueTrue;
			if (valueFalse != nullptr)
				delete valueFalse;
		}

		float evaluate(Game::Object* obj) override
		{
			if (condition == nullptr)
				return 0;

			if (condition->allow(obj))
			{
				if (valueTrue != nullptr)
					return valueTrue->evaluate(obj);
				else
					return 0;
			}
			else
			{
				if (valueFalse != nullptr)
					return valueFalse->evaluate(obj);
				else
					return 0;
			}
		}

		Allow::Base *condition;
		Base *valueTrue, *valueFalse;
	};

}
