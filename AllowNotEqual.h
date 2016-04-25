#pragma once
#include "AllowBase.h"
#include "control.h"

namespace Allow
{
	class NotEqual : public Base
	{
	public:
		NotEqual(Game::Object*_toCompare)
			: toCompare(_toCompare)
		{

		}

		bool allow(Game::Object *obj)
		{
			return toCompare != obj;
		}

		Game::Object *toCompare;
	};

}
