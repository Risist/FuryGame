#pragma once
#include "AllowBase.h"
#include "EvaluateBase.h"

namespace Allow
{

	class StatInRange : public Base
	{
	public:
		StatInRange(Evaluate::Base* _value = nullptr, Evaluate::Base *_min = nullptr, Evaluate::Base *_max = nullptr)
			: min(_min), max(_max), value(_value)
		{

		}
		~StatInRange()
		{
			if (value != nullptr)
				delete value;
			if (min != nullptr)
				delete min;
			if (max != nullptr)
				delete max;
		}

		bool allow(Game::Object* obj) override
		{
			float v = value->evaluate(obj);

			if (min != nullptr)
			{
				float fMin = min->evaluate(obj);
				if (v < fMin)
					return false;
			}

			if (max != nullptr)
			{
				float fMax = max->evaluate(obj);
				if (v > fMax)
					return false;
			}


			return true;
				
		}


		// 
		Evaluate::Base *value, *min, *max;
	};


}

