#pragma once
#include "GameObject.h"

namespace Evaluate
{
	class Base
	{
	public:
		Base(){}
		virtual ~Base() {}

		virtual float evaluate(Game::Object *obj) = 0;

	};

}

