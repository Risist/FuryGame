#include "Bullet.h"
#include "GameWorld.h"

extern Game::World world;

Bullet::Bullet(Game::Object *owner) : Projectile(owner)
{
}

void Bullet::onInit()
{
	Projectile::onInit();

	model.deserialize("model_projectile.txt");
	getHp().position = 70;
	getHp().resetVelocity = 0;

	addCollider(CircleCollider(Vector2D(), 50) );

	getPos().position = getOwner()->getPosC().position;
	getRot().position = getOwner()->getRotC().position;
}

void Bullet::onUpdate(float dt)
{
	Projectile::onUpdate(dt);

	onPush(Vector2D(0, -5).getRotated(getRotC().position), nullptr);
	onDamage(-1, nullptr);

	checkForCollision(world);
}

void Bullet::onCollision(Game::Object* other, const pair<int, int >& firstColliderId)
{
	Vector2D toOther = other->getPosC().position - getPosC().position;

	other->getPos().addForce(toOther.normalised() * 50);
}
