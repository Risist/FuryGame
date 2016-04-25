#pragma once
#include "GameObject.h"


class EfectCollisionResponse : public Game::Efect
{
public:
	EfectCollisionResponse( float _toOtherRatio = 0, float _springRatio = 0, float _maxSpringForce = 999999, const Vector2D& _constRatio = Vector2D() );

	void onUpdate(float dt) override;
	void onCollision(const ColliderInfo& otherCollider) override;

	float toOtherRatio;
	float springRatio, maxSpringForce;
	Vector2D constRatio;
};

