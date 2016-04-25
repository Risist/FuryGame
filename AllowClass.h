#pragma once

namespace Allow
{
	template<class Type>
	class Class : public Base
	{
	public:
		Class(bool negation = false)
			: Base(negation)
		{

		}

		bool allow(Game::Object *obj) override
		{
			bool b = dynamic_cast<Type*>(obj) != nullptr;
			return getWithNegation(b);
		}
	};


}

