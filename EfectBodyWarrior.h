#pragma once
#include "GameWorld.h"
#include "GameMultiEfectNoInteract.h"
#include "efects.h"
#include "EfectWeapon.h"
#include "GameCompetitor.h"

class EfectBodyWarrior : public Game::MultiEfectNoInteract
{
public:
	EfectBodyWarrior(size_t idWeapon= 0);

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*) Game::MultiEfectNoInteract::getOwner();
	}

	void loadModels();

	void onInit() override;
	void onUpdate( float dt) override;
	void onDisplay(Camera& cam) override;

	bool onDeath() override;

	EfectModel *efBody, *efHead, *efArmLeft, *efArmRight;
	EfectWeapon *efWeaponLeft, *efWeaponRight;
	size_t idWeapon;

	bool alive;
};

