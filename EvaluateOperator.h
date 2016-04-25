#pragma once
#include "EvaluateBase.h"

namespace Evaluate
{
	class Operator : public Base
	{
	public:
		enum Operation
		{
			addiction,
			substraction,
			multiplication,
			division
		}operation;

		Operator(const initializer_list<Base*>& _elements = {}, Operation _operation = addiction );
		~Operator();

		float evaluate(Game::Object *obj) override;

		

		vector<Base*> elements;
	};

}
