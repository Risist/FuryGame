#include "EfectCheckForCollisionComponent.h"


EfectCheckForCollisionComponent::EfectCheckForCollisionComponent(
	Game::Object* _obj1, size_t _obj1IdMin, int _obj1IdMax,
	Game::Object* _obj2, size_t _obj2IdMin, int _obj2IdMax
	)
	: obj1(_obj1), obj1IdMin(_obj1IdMin), obj1IdMax(_obj1IdMax),
	obj2(_obj2), obj2IdMin(_obj2IdMin), obj2IdMax(_obj2IdMax)
{
}


void EfectCheckForCollisionComponent::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	//obj1->checkForCollision(obj2, obj1IdMin, obj1IdMax, obj2IdMin, obj2IdMax);

	//if (obj2->isCheckingForCollision == true)
		//obj2->checkForCollision(obj1, obj2IdMin, obj2IdMax, obj1IdMin, obj1IdMax);
	if (obj1 == nullptr || obj2 == nullptr)
		return;


	auto itMax1 = obj1->colliders.begin() + (obj1IdMax < 0 ? obj1->colliders.size() : obj1IdMax);
	auto itMax2 = obj2->colliders.begin() + (obj2IdMax < 0 ? obj2->colliders.size() : obj2IdMax);
	for (auto it1 = obj1->colliders.begin() + obj1IdMin; it1 != itMax1; ++it1)
		for (auto it2 = obj2->colliders.begin() + obj2IdMin; it2 != itMax2; ++it2)
			it1->checkForColliion(*it2, true, true);
}
