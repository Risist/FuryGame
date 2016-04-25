#pragma once
#include "GameObject.h"

namespace Game
{
	// game object without running onInteract event for efect
	// used for materials
	class ObjectNoInteract : public Game::Object
	{
	public:

		void onInteract(float force, size_t resId, Game::Object *obj) override
		{
			resource_f[resId].addForce(force);
		}
		void onInteract(const Vector2D& force, size_t resId, Game::Object *obj) override
		{
			resource_v2[resId].addForce(force);
		}
	};
}

