#pragma once
#include "CircleCollider.h"

namespace Game
{
	class Efect;
}

class ColliderInfo
{
public:
	ColliderInfo(const CircleCollider& collider = CircleCollider(), Game::Efect* efect = nullptr, sf::Sprite* connectedTo = nullptr);


	void checkForColliion(const ColliderInfo& other, bool otherRunOnCollision = true, bool myRunOnCollision = true) const;
	CircleCollider getActualCollider() const;

	CircleCollider collider;
	sf::Sprite *connectedTo;
	Game::Efect *efect;
};

