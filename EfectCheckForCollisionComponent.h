#pragma once
#include "GameWorld.h"

class EfectCheckForCollisionComponent : public Game::Efect
{
public:
	EfectCheckForCollisionComponent(
		Game::Object* obj1 = nullptr, size_t obj1IdMin = 0, int obj1IdMax = -1,
		Game::Object* obj2 = nullptr, size_t obj2IdMin = 0, int obj2IdMax = -1);

	Game::Object *obj1, *obj2;
	size_t obj1IdMin;
	int obj1IdMax;
	
	size_t obj2IdMin;
	int obj2IdMax;

	void onUpdate(float dt) override;

};

