#pragma once
#include "AllowBase.h"

namespace Allow
{

	class Collider : public Base
	{
	public:
		Collider( const CircleCollider& _collider, sf::Sprite* _connectedTo = nullptr, bool negation = false)
			: collider(_collider), connectedTo(_connectedTo), Base(negation)
		{

		}

		bool allow(Game::Object* obj) override
		{
			CircleCollider _collider;

			// get real collider 
			if (connectedTo != nullptr)
				_collider = collider.getColliderAccordingToSprite(*connectedTo);
			else
				_collider = collider;

			// check for collision
			bool b = obj->isOnCollision(collider);

			// return right value
			return getWithNegation(b);
		}

		sf::Sprite *connectedTo;
		CircleCollider collider;
	};

}
