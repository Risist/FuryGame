#pragma once
#include "EvaluateBase.h"

namespace Evaluate
{
	class RandRange : public Base
	{
	public:
		RandRange(Base *_min = nullptr, Base *_max = nullptr)
			: min(_min), max(_max)
		{

		}
		~RandRange()
		{
			if (min != nullptr)
				delete min;
			if (max != nullptr)
				delete max;
		}

		float evaluate(Game::Object *obj) override
		{
			if (min == nullptr && max != nullptr)
				return max->evaluate(obj);
			else if (min != nullptr && max == nullptr)
				return min->evaluate(obj);
			else if ( min == nullptr && max == nullptr)
				return 0;

			return randRange( min->evaluate(obj), max->evaluate(obj));
		}

		Base *min, *max;
	};

}

