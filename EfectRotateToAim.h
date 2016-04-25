#pragma once
#include "GameEfect.h"
#include "GameObject.h"

class EfectRotateToAim : public Game::Efect
{
public:
	EfectRotateToAim(Game::Object*aim = nullptr, float force = 0.f, float minDiff = 0.f );

	void onUpdate(float dt) override;

	Game::Object *aim;
	float force;
	float minDiff;
};



