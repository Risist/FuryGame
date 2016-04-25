#pragma once
#include "GameObject.h"

class EfectUpdateModel : public Game::Efect
{
public:
	EfectUpdateModel(Model *model = nullptr, sf::Sprite *connectedTo = nullptr, bool updatePosition = true, bool updateRotation = true);

	void onUpdate(float dt) override;

	Model* model;
	sf::Sprite *connectedTo;
	bool updatePosition, updateRotation;
};

