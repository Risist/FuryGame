#pragma once
#include "GameObject.h"

class EfectFollowCam : public Game::Efect
{
public:
	EfectFollowCam(sf::Sprite * connectedTo = nullptr, float addictionalRotation = 0, float cameraOffset = -350, bool updatePosition = true, bool updateRotation = true);

	void onDisplay(Camera& cam) override;

	sf::Sprite *connectedTo;
	float cameraOffset, addictionalRotation;
	bool updatePosition, updateRotation;
};

