#include "EfectCollisionResponse.h"


EfectCollisionResponse::EfectCollisionResponse(float _toOtherRatio, float _springRatio, float _maxSpringForce, const Vector2D& _constRatio)
	: toOtherRatio(_toOtherRatio), springRatio(_springRatio), maxSpringForce(_maxSpringForce), constRatio(_constRatio)
{
}

bool logger = false;
void EfectCollisionResponse::onUpdate(float dt)
{
	Efect::onUpdate(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		logger = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		logger = false;
}
void EfectCollisionResponse::onCollision( const ColliderInfo& otherCollider)
{
	Efect::onCollision( otherCollider);

	if (colliderInfo == nullptr)
		return;

	Vector2D toOther = otherCollider.getActualCollider().center - colliderInfo->getActualCollider().center;

	if (toOther.isZero())
		return;

	Vector2D toOtherNormalised = toOther.normalised();
	toOther *= springRatio / toOther.getLenghtSq() * (colliderInfo->collider.range + otherCollider.collider.range);

	if (toOther.getLenghtSq() > maxSpringForce*maxSpringForce)
	{
		toOther = toOtherNormalised * maxSpringForce;
	}


	Vector2D force = toOtherNormalised * toOtherRatio + toOther;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !toOther.isZero())
	
	
	

	if (logger && !toOther.isZero())
	{
		//cout << "force = " << force << "\n";
		cout << "ToOther = " << toOther << "\n";
		//cout << "ToOtherNormalised = " << toOtherNormalised << "\n";
		//cout << "\n";
	}

	otherCollider.efect->onPush(force);

	/*Vector2D toOther = otherCollider.getActualCollider().center - colliderInfo->getActualCollider().center;
	//Vector2D toOther = other->getPosC().position - getOwner()->getPosC().position;
	Vector2D velocity = otherCollider.efect->getPosC().velocity - getOwner()->getPosC().velocity;

	if ( !toOther.isZero() )
	toOther /= toOther.getLenghtSq();
	if (!velocity.isZero())
		velocity /= velocity.getLenghtSq();

	Vector2D force = toOther.normalised() * toOtherRatio + velocity * velocityRatio + constRatio;
	otherCollider.efect->onPush( force );/**/

}