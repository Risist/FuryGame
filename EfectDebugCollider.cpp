#include "EfectDebugCollider.h"


EfectDebugCollider::EfectDebugCollider(const Control::Input& _input, const Color& _color, const Color& _colorOnCollision)
	: input(_input), color(_color), colorOnCollision(_colorOnCollision)
{
}


void EfectDebugCollider::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);

	if ( input.isReady() )
		for (size_t i = 0; i < getOwner()->colliders.size(); ++i)
		{
			auto coll = getOwner()->colliders[i].getActualCollider();
			coll.display(cam, colliding ? colorOnCollision : color);
		}


	colliding = false;
}

void EfectDebugCollider::onCollision(const ColliderInfo& otherCollider)
{
	Efect::onCollision(otherCollider);

	colliding = true;
}
