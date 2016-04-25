#include "EfectDamageOnCollision.h"
#include <limits>

EfectDamageOnCollision::EfectDamageOnCollision(float _flatDamage, float _springDamage, float _maxSpring)
	:flatDamage(_flatDamage), springDamage(_springDamage), maxSpring(_maxSpring)
{
}


void EfectDamageOnCollision::onCollision(const ColliderInfo& otherCollider)
{
	Efect::onCollision(otherCollider);

	if (otherCollider.efect != nullptr)
	{
		Vector2D toOther = otherCollider.getActualCollider().center - colliderInfo->getActualCollider().center;

		float force = flatDamage;

		if (!toOther.isZero() && springDamage*springDamage > numeric_limits<float>::min() )
		{
			// prepare toOther to being an inverse vector
			toOther *= (colliderInfo->collider.range + otherCollider.collider.range) / toOther.getLenghtSq();

			// check is the vector in proper range
			if (toOther.getLenghtSq() > maxSpring*maxSpring/(springDamage*springDamage))
			{
				toOther = toOther.normalised() * maxSpring/springDamage;
			}

			force += toOther.getLenght()*springDamage;
			//cout << "toOther: " << toOther.getLenght() << "\n";
		}
		//cout << "dmg: " << force << "\n";
		otherCollider.efect->onDamage(force);



		//Vector2D v = getOwner()->getPosC().velocity - otherCollider.efect->getPosC().velocity;
		//otherCollider.efect->onDamage(flatDamage + v.getLenght() * velocityDamage, getOwner());

		//cout << "dmg: " << flatDamage + v.getLenght() * velocityDamage << "\n";
	}


}