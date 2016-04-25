#pragma once
#include "GameWorld.h"
#include "control.h"

class EfectDeathOutOfCollider : public Game::Efect
{
public:
	EfectDeathOutOfCollider(vector<CircleCollider> *collidersSaveZone = nullptr, sf::Sprite *connectedTo = nullptr,
		float damageOut = -100,
		const Control::Input& inputDebug = Control::Input(), const Color& clDebug = Color(100, 200, 100, 150) );

	void onInit() override;

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	Control::Input inputDebug;
	vector<CircleCollider> *collidersSaveZone;
	sf::Sprite *connectedTo;
	Color clDebug;
	float damageOut;
};


