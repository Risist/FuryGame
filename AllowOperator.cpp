#include "AllowOperator.h"


namespace Allow
{
	Operator::Operator(const initializer_list<Base*>& _elements, Operation _operation, bool negation)
		: Base(negation), operation(_operation)
	{
		for each (auto it in _elements)
			if (it != nullptr)
			{
				elements.push_back(it);
			}
	}
	Operator::~Operator()
	{
		for (int i = 0; i < elements.size(); ++i)
			if (elements[i] != nullptr)
				delete elements[i];
	}

	bool Operator::allow(Game::Object* obj)
	{
		switch (operation)
		{
		case And:
			for each (auto &it in elements)
				if (it->allow(obj) == false)
					return getWithNegation(false);
			return getWithNegation(true);
		
		case Or:
			for each (auto &it in elements)
				if (it->allow(obj) == true)
					return getWithNegation(true);
			return getWithNegation(false);
		case Xor:
		{
			bool b = false;
			for each (auto &it in elements)
				if (it->allow(obj) == true)
				{
					if (b == true)
						return getWithNegation(false);
					else
						b = true;
				}
			return getWithNegation(true);
		}
		default:
			return getWithNegation(false);
		}	
	}


}