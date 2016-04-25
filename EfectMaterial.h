#pragma once
#include "GameWorld.h"

class EfectMaterial : public Game::Efect
{
public:
	enum Type
	{
		f,
		v2
	}type;
	EfectMaterial( size_t resId = 0 , Type type = f, Efect *toAct = nullptr, float forceRatio = 1);

	void onInteract(float force, size_t resId, Game::Object *causer) override;
	void onInteract(const Vector2D& force, size_t resId, Game::Object *causer) override;

	Efect *toAct;
	float forceRatio;

	size_t resId;
	
};

