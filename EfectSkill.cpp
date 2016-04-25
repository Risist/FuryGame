#include "EfectSkill.h"
extern Game::World world;

EfectSkill::EfectSkill(const Control::Timer& _timer, const string& _inputName)
	: timer(_timer), inputName(_inputName)
{
}





void EfectSkill::addProjectile(Game::Projectile* projectile)
{
	projectile->setOwner(getOwner() );
	world.push_back(projectile);
}
