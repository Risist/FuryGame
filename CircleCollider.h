#pragma once
#include "utility.h"
#include "Camera.h"

class CircleCollider
{
public:
	CircleCollider( const Vector2D& _center = Vector2D(), float _range = 0);

	// tells whether the colliders are colliding each other
	bool isOnCollision(const CircleCollider& other) const;


	CircleCollider getColliderAccordingToSprite(const sf::Sprite& sp) const;

	void display(Camera& cam, const Color& color) const;
	void display(RenderWindow& cam, const Color& color) const;

	Vector2D center;
	float range;
};

