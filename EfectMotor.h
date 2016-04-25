#pragma once
#include "GameWorld.h"

class EfectMotor : public Game::Efect
{
public:
	EfectMotor( const Vector2D& _force = Vector2D(), bool _accordingToOwner = true, bool _trueForce = false );

	void onUpdate(float dt) override;

	Vector2D force;
	bool accordingToOwner;
	bool trueForce;
};

