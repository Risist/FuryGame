#pragma once
#include "GameMultiEfect.h"
namespace Game
{
	class MultiEfectNoInteract : public MultiEfect
	{
	public:

		void onInteract(float force, size_t resId, Game::Object *obj) override
		{
			Game::Efect::onInteract(force, resId, obj);
		}
		void onInteract(const Vector2D& force, size_t resId, Game::Object *obj) override
		{
			Game::Efect::onInteract(force, resId, obj);
		}
	};

}
