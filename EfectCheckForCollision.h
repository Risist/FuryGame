#pragma once
#include "GameWorld.h"

class EfectCheckForCollision : public Game::Efect
{
public:
	EfectCheckForCollision(vector<Game::Object*> *world);

	void onInit();
	void onUpdate(float dt);

	vector<Game::Object*> *world;
};

