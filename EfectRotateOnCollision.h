#pragma once
#include "GameWorld.h"

class EfectRotateOnCollision : public Game::Efect
{
public:
	EfectRotateOnCollision(float force = 0, sf::Sprite *anchorObject = nullptr, float addictionalAngle =0, const Vector2D& anchorPoint = Vector2D() );

	sf::Sprite *anchorObject;
	Vector2D anchorPoint;
	float force;
	float addictionalAngle;

	void onInteract(const Vector2D& force, size_t resId, Game::Object *causer) override;
};

