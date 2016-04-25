#include "Efect2WeaponMaterial.h"


Efect2WeaponMaterial::Efect2WeaponMaterial(
	Game::Object* _obj1, size_t _obj1IdMin, int _obj1IdMax, size_t _res1, float _force1,
	Game::Object* _obj2, size_t _obj2IdMin, int _obj2IdMax, size_t _res2, float _force2)
	: obj1(_obj1), obj1IdMin(_obj1IdMin), obj1IdMax(_obj1IdMax), idRes1(_res1), force1(_force1),
	obj2(_obj2), obj2IdMin(_obj2IdMin), obj2IdMax(_obj2IdMax), idRes2(_res2), force2(_force2)
{
}

void Efect2WeaponMaterial::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);
	bool isOnCollision = false;

	if (obj1 == nullptr || obj2 == nullptr)
		return;


	auto itMax1 = obj1->colliders.begin() + (obj1IdMax < 0 ? obj1->colliders.size() : obj1IdMax);
	auto itMax2 = obj2->colliders.begin() + (obj2IdMax < 0 ? obj2->colliders.size() : obj2IdMax);
	for (auto it1 = obj1->colliders.begin() + obj1IdMin; it1 != itMax1; ++it1)
		for (auto it2 = obj2->colliders.begin() + obj2IdMin; it2 != itMax2; ++it2)
			if (it1->getActualCollider().isOnCollision(it2->getActualCollider()))
			{
				isOnCollision = true;
				goto next;
			}
	next:


	if (isOnCollision)
	{
		getRes1().addForce(force1);
		getRes2().addForce(force2);
	}

}
