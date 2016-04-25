#include "EfectMaxHealth.h"


EfectMaxHealth::EfectMaxHealth(float _maxHealth, ExceedMode _exceedMode, float _dmgRatio)
	: maxHealth(_maxHealth), exceedMode(_exceedMode), dmgRatio(_dmgRatio)
{
}


void EfectMaxHealth::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (getOwner()->getHpC().position <= maxHealth)
		return; // not needed any reaction

	if ( exceedMode == cut)
		getOwner()->getHp().position = maxHealth;
	else if (exceedMode == dmgForce)
	{
		float dmg = maxHealth - getOwner()->getHp().position ;
		getOwner()->getHp().position = maxHealth;
		getOwner()->onDamage(dmg * dmgRatio);
	}
	else if ( exceedMode == dmgChange)
	{
		float dmg = maxHealth - getOwner()->getHp().position;
		getOwner()->getHp().position = maxHealth + dmg *dmgRatio * getOwner()->getHpC().inverseMass;
	}

	/*switch (exceedMode)
	{
	none:
		// do nothing
		break;
	cut:
		getOwner()->getHp().position = maxHealth;
		break;
	dmgForce:
		getOwner()->onDamage(maxHealth - getOwner()->getHp().position);
		break;
	dmgChange:
		getOwner()->getHp().position += (maxHealth - getOwner()->getHp().position) * getOwner()->getHp().inverseMass;
		break;
	default:
		break;
	}*/
}