#include "ColliderInfo.h"
#include "GameEfect.h"

ColliderInfo::ColliderInfo(const CircleCollider& _collider, Game::Efect* _efect, sf::Sprite* _connectedTo)
	: collider(_collider), efect(_efect), connectedTo(_connectedTo)
{
}




void ColliderInfo::checkForColliion(const ColliderInfo& other, bool otherRunOnCollision, bool myRunOnCollision) const
{
	if (
		efect != nullptr && other.efect != nullptr && efect->activated && other.efect->activated
		&& getActualCollider().isOnCollision( other.getActualCollider() )
		)
	{
		efect->setColliderInfo( (ColliderInfo*)this );
		other.efect->setColliderInfo( (ColliderInfo*)&other);

		if (myRunOnCollision)
			efect->onCollision( other);

		if (otherRunOnCollision )
			other.efect->onCollision(*this);
	}
}

CircleCollider ColliderInfo::getActualCollider() const
{
	CircleCollider c1 = collider;
	if (connectedTo != nullptr)
		c1 = c1.getColliderAccordingToSprite(*connectedTo);
	return c1;
}