#pragma once
#include "GameEfect.h"

class EfectSpringJoint : public Game::Efect
{
public:
	EfectSpringJoint( Game::Object *myToAffect = nullptr, Game::Object *otherToAffect = nullptr, float forceRatio = 0,
		sf::Sprite *myConnectedTo = nullptr, sf::Sprite *otherConnectedTo = nullptr, 
		const Vector2D& myAnchor = Vector2D(), const Vector2D& otherAnchor = Vector2D());

	void onUpdate(float dt) override;

	Game::Object *myToAffect, *otherToAffect;
	sf::Sprite *myConnectedTo, *otherConnectedTo;
	Vector2D myAnchor, otherAnchor;

	float forceRatio;


};

