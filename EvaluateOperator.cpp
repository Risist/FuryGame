#include "EvaluateOperator.h"
#include <limits>


namespace Evaluate
{

	Operator::Operator(const initializer_list<Base*>& _elements, Operation _operation)
		: operation(_operation)
	{
		for each ( auto it in _elements)
			if (it != nullptr)
				elements.push_back(it);
	}


	Operator::~Operator()
	{
		for each (auto it in elements)
			if (it != nullptr)
				delete it;
	}

	float Operator::evaluate(Game::Object *obj)
	{
		float r;

		if (operation == addiction)
		{
			r = 0;
			for each(auto it in elements)
				if (it != nullptr)
					// to make sure the noumber is not too big/small
					r = clamp(r + it->evaluate(obj), -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
			return r;
		}
		else if (operation == substraction)
		{
			r = 0;
			for each(auto it in elements)
				if (it != nullptr)
					// to make sure the noumber is not too big/small
					r = clamp(r - it->evaluate(obj), -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
			return r;
		}
		else if (operation == multiplication)
		{
			r = 1;
			for each(auto it in elements)
				if (it != nullptr)
				{
					float v = it->evaluate(obj);

					// in this case futher computations are not needed
					if (v*v < std::numeric_limits<float>::min())
						return 0;
					else
						// to make sure the noumber is not too big/small
						r = clamp(r*v, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
				}
			return r;
		}
		else if (operation == division)
		{
			r = 1;
			for each(auto it in elements)
				if (it != nullptr)
				{
					float v = it->evaluate(obj);

					if (v*v < std::numeric_limits<float>::min())
					{
						r = std::numeric_limits<float>::infinity() * ( v > 0 ? 1 : -1);
						return r;
					}
					else if (v > std::numeric_limits<float>::infinity() ||
						v < -std::numeric_limits<float>::infinity())
						return 0;
					else
						// to make sure the noumber is not too big/small
						r = clamp(r / v, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
				}
			return r;
		}


		return -2.5;
	}


}