#pragma once
#include "GameWorld.h"

class EfectMaxHealth : public Game::Efect
{
public:
	enum ExceedMode // if hp exceeds maxValue do:
	{
		none, // nothing
		cut, // cut value of health to be equal to maxHealth
		dmgForce, // value above is changed to dmg and will hurt the owner by aplying force
		dmgChange // value above is changed to dmg and will hurt the owner by instantly change value of healt
	}exceedMode;

	EfectMaxHealth(float maxHealth = 100, ExceedMode exceedMode = none, float dmgRatio = 1);

	void onUpdate(float dt) override;

	
	float maxHealth;
	float dmgRatio;
};

