#pragma once
#include "GameObject.h"

namespace Game
{

	class Projectile : public Object
	{
	public:
		Projectile(Object *owner = nullptr);

		Object* getOwner()
		{
			return owner;
		}
		void setOwner(Object* newOwner)
		{
			owner = newOwner;
		}
		bool hasOwner()
		{
			return owner != nullptr;
		}

	private:
		Object* owner;
	};
}

