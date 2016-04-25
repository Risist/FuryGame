#include "EfectWeapon2hAxe.h"
#include "EfectSwordMaterial.h"

EfectWeapon2hAxe::EfectWeapon2hAxe(sf::Sprite* _handSprite, sf::Sprite* _handSprite2)
	: EfectWeapon(_handSprite, "rightX", "rightY"), handSprite2(_handSprite2)
{
}


void EfectWeapon2hAxe::onInit()
{
	EfectWeapon::onInit();

	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_axe2h.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		addEfect(efModel = new EfectModel(stream, &middleHand, false, false));
	}

	
	getOwner()->allModels.push_back(&efModel->model);

	// Animations
	getOwner()->addAnimation("arms", Animation("animation_axe2h_arms.txt"));
	getOwner()->addAnimation("push", Animation("animation_axe2h_push.txt"));

	getOwner()->addAnimation("grab", Animation("animation_axe2h_grab.txt"));
	{
		auto anim = getOwner()->getAnimation("grab");
		anim.update(getOwner()->allModels, anim.getStepMax());
	}

	getResX().resetVelocity = 0.9;
	getResX().inverseMass = -0.3f;

	getResY().resetVelocity = 0.85;
	getResY().inverseMass = -0.45f;

	//getOwner()->getPos().inverseMass *= 0.875;

	// stick
	auto efStick = new Game::MultiEfect;
	addEfect(efStick);

	efStick->addEfect(efDmg = new EfectDamageOnCollision(-0.025, -0.02, 0.25));
	efStick->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efStick->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efStick->addEfect(new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efStick->addEfect(new EfectSwordMaterial(idResX, -1, 1., 0, &efModel->model));
	efStick->addEfect(new EfectSwordMaterial(idResY, -1, 1., 0, &efModel->model, 90));


	efStick->addEfect(efCollision = new EfectCollisionResponse(1., 5., 20));

	for (float i = -4; i < 8; ++i)
		getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 30 * i + 5), 17.5), efStick, &efModel->model));

	auto efEdge = new Game::MultiEfect;
	addEfect(efEdge);

	efEdge->addEfect(efDmg = new EfectDamageOnCollision(0.3, -0.5, 10.));
	efEdge->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efEdge->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efEdge->addEfect(new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efEdge->addEfect(new EfectSwordMaterial(idResX, -1, 2.5, 0, &efModel->model));
	efEdge->addEfect(new EfectSwordMaterial(idResY, -1, 1.5, 0, &efModel->model, 90));

	efEdge->addEfect(efCollision = new EfectCollisionResponse(1, 7.5, 20.));

	//for (float i = -8; i > -13; --i)
		//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 25 * i + 30), 15), efEdge, &efModel->model));

	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(20, -215), 22.5), efEdge, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-10, -160 ), 40), efEdge, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-50, -140), 25), efEdge, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-75, -120), 20), efEdge, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-90, -85), 20), efEdge, &efModel->model));

	getOwner()->layerCollider.collider.center.y = 0;
	getOwner()->layerCollider.collider.range = 360;
}

void EfectWeapon2hAxe::onUpdate(float dt)
{
	middleHand.setPosition(Vector2D(handSprite->getPosition() + handSprite2->getPosition()) * 0.5);

	Vector2D v1(0, 1); v1.rotate(handSprite->getRotation());
	Vector2D v2(0, 1); v2.rotate(handSprite2->getRotation());
	float angle = (v1 - v2).angle();
	middleHand.setRotation(angle);

	middleHand.setScale(Vector2D(handSprite->getScale() + handSprite2->getScale()) * 0.5);


	Game::MultiEfectNoInteract::onUpdate(dt);

	if (pressed)
	{
		getResX().addForce(getOwner()->getDrag().x * strenghtX);
		getResY().addForce(getOwner()->getDrag().y * strenghtY);

		getOwner()->getRot().inverseMass = 0.335;
	}
	else
	{
		getResX().addForce(-getOwner()->getDrag().x * 0.15);

		getOwner()->getRot().inverseMass = 1.;
	}

	getResX().inverseMass = -0.55 + getOwner()->getAnimation("push").getPercentStep() * 0.3;

	getOwner()->getAnimation("arms").updateInRange(getOwner()->allModels, 1. * getResX().velocity);

	getOwner()->getAnimation("push").updateInRange(getOwner()->allModels, 1. * getResY().velocity);
	//getOwner()->getAnimation("push").updateInRange(getOwner()->allModels, 0.05 * getResY().velocity * getOwner()->getAnimation("arms").step);

	pressed = false;
}