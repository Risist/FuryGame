#pragma once
#include "AllowBase.h"

namespace Allow
{
	class Operator : public Base
	{
	public:

		// Several basic types of operation supported by this class
		enum Operation
		{
			And,
			Or,
			Xor
		}operation;

		Operator(const initializer_list<Base*>& _elements = {}, Operation _operation = And, bool negation = false );
		~Operator();

		bool allow(Game::Object *obj) override;

		
		


		vector<Base*> elements;
	};

}

