#include "EfectWeaponAxe1h.h"


EfectWeaponAxe1h::EfectWeaponAxe1h(sf::Sprite* _handSprite)
	:handSprite(_handSprite)
	, dmgRatio(-0.25f), pushRatio(0.25),
	clampDmg(-10., -0.01), clampPush(0.5, 4),
	changeRotation(0.2f)
{
}


void EfectWeaponAxe1h::onInit()
{
	Game::Efect::onInit();

	// addResource
	idResX = getOwner()->addResource(Resource<float>());
	getResX().resetVelocity = 0.9;
	getResX().inverseMass = -0.2f;

	idResY = getOwner()->addResource(Resource<float>());
	getResY().resetVelocity = 0.9;
	getResY().inverseMass = -0.2f;



	// weapon model;
	getOwner()->addEfect(efModel = new EfectModel("model_axe.txt", handSprite, false, false));

	// Animations
	getOwner()->addAnimation("atackX", Animation("swordAnim.txt"));
	getOwner()->addAnimation("atackY", Animation("swordAnimPush.txt"));

	// efect After dealing damage
	auto efSword = new Game::MultiEfect;
	getOwner()->addEfect(efSword);

	efSword->addEfect(efDmg = new EfectDamageOnCollision(dmgRatio));
	efSword->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.1))));
	efSword->addEfect(efCollision = new EfectCollisionResponse(pushRatio));

	// colliders blade
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(20, 40), 13), efSword, efModel->model.childDown));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(20, 20), 13), efSword, efModel->model.childDown));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(20, 0), 13), efSword, efModel->model.childDown));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(5, -20), 20), efSword, efModel->model.childDown));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-10, -50), 20), efSword, efModel->model.childDown));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-15, -80), 15), efSword, efModel->model.childDown));


	auto efStick = new Game::MultiEfect;
	getOwner()->addEfect(efStick);

	efStick->addEfect(efCollision = new EfectCollisionResponse(pushRatio));

	// colloders stick
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 40), 13), efStick, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 20), 13), efStick, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 0), 13), efStick, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -20), 13), efStick, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -40), 13), efStick, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -60), 13), efStick, &efModel->model));
}

void EfectWeaponAxe1h::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (getOwner()->isPressed("s2"))
	{
		getResX().addForce(getOwner()->getDrag().x);
		getResY().addForce(getOwner()->getDrag().y);
		//getOwner()->getRot().inverseMass = min(changeRotation, getOwner()->getRot().inverseMass);
		getRot().inverseMass = 0.3;
		getRot().resetVelocity = 0.75;
	}

	getOwner()->getAnimation("atackX").updateInRange(getOwner()->allModels, getResX().velocity);
	getOwner()->getAnimation("atackY").updateInRange(getOwner()->allModels, getResY().velocity);


	float velocity = Vector2D(getResX().velocity, getResY().velocity).getLenght();

	efCollision->toOtherRatio = clamp(pushRatio * velocity, clampPush.x, clampPush.y);
	efDmg->flatDamage = clamp(dmgRatio * velocity, clampDmg.x, clampDmg.y);
}