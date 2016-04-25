#pragma once
#include "GameWorld.h"

class Efect2WeaponMaterial : public Game::Efect
{
public:
	Efect2WeaponMaterial(Game::Object* obj1 = nullptr, size_t obj1IdMin = 0, int obj1IdMax = -1, size_t res1 = 0, float force1 = 0,
		Game::Object* obj2 = nullptr, size_t obj2IdMin = 0, int obj2IdMax = -1, size_t res2 = 0, float force2 = 0);

	void onUpdate(float dt) override;

	Game::Object *obj1, *obj2;
	size_t obj1IdMin;
	int obj1IdMax;

	size_t obj2IdMin;
	int obj2IdMax;

	Resource<float>& getRes1()
	{
		return getOwner()->getResource_f(idRes2);
	}
	Resource<float>& getRes2()
	{
		return getOwner()->getResource_f(idRes1);
	}
	size_t idRes1, idRes2;

	float force1, force2;
};

