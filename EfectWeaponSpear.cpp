#include "EfectWeaponSpear.h"
#include "EfectSwordMaterial.h"


EfectWeaponSpear::EfectWeaponSpear(sf::Sprite* _handSprite, sf::Sprite* _handSprite2)
	: EfectWeapon(_handSprite, "rightX", "rightY"), handSprite2(_handSprite2)
{
}


void EfectWeaponSpear::onInit()
{
	EfectWeapon::onInit();

	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_spear.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		addEfect(efModel = new EfectModel(stream, &middleHand, false, false));
	}
	getOwner()->allModels.push_back( &efModel->model );

	// Animations
	getOwner()->addAnimation("arms", Animation("animation_spear_arms.txt"));
	getOwner()->addAnimation("push", Animation("animation_spear_push.txt"));

	getOwner()->addAnimation("grab", Animation("animation_spear_grab.txt"));
	{
		auto anim = getOwner()->getAnimation("grab");
		anim.update(getOwner()->allModels, anim.getStepMax());
	}

	getResX().resetVelocity = 0.9;
	getResX().inverseMass = -0.3f;

	getResY().resetVelocity = 0.9;
	getResY().inverseMass = -0.8f;


	//getOwner()->getPos().inverseMass *= 0.925;

	// stick
	auto efStick = new Game::MultiEfect;
	addEfect(efStick);

	efStick->addEfect(efDmg = new EfectDamageOnCollision(-0.025, -0.02, 0.25));
	efStick->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efStick->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efStick->addEfect(new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efStick->addEfect(new EfectSwordMaterial(idResX, -1, 1, 0, &efModel->model));
	efStick->addEfect(new EfectSwordMaterial(idResY, -1, 1, 0, &efModel->model, 90));


	efStick->addEfect(efCollision = new EfectCollisionResponse(1., 5., 20));

	for (float i = -6; i < 9; ++i)
		getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 30*i+15), 17.5), efStick, &efModel->model));
	
	auto efEdge= new Game::MultiEfect;
	addEfect(efEdge);

	efEdge->addEfect(efDmg = new EfectDamageOnCollision(0.55, -0.55, 6.5));
	efEdge->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efEdge->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efEdge->addEfect(new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efEdge->addEfect(new EfectSwordMaterial(idResX, -1, 4.25, 0, &efModel->model));
	efEdge->addEfect(new EfectSwordMaterial(idResY, -1, 1., 0, &efModel->model, 90));

	//efEdge->addEfect(efCollision = new EfectCollisionResponse(5.5, -5.25, 20.5));
	efEdge->addEfect(efCollision = new EfectCollisionResponse(1.5, 4.5, 15));


	for (float i = -10; i > -13; --i)
		getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 25 * i + 50), 20.), efEdge, &efModel->model));

	getOwner()->layerCollider.collider.center.y = 0;
	getOwner()->layerCollider.collider.range = 410;

}

void EfectWeaponSpear::onUpdate(float dt)
{
	middleHand.setPosition(Vector2D(handSprite->getPosition() + handSprite2->getPosition()) * 0.5);

	Vector2D v1(0, 1); v1.rotate(handSprite->getRotation());
	Vector2D v2(0, 1); v2.rotate(handSprite2->getRotation());
	float angle = (v1 - v2).angle() ;
	middleHand.setRotation(angle);

	middleHand.setScale(Vector2D(handSprite->getScale() + handSprite2->getScale()) * 0.5);


	Game::MultiEfectNoInteract::onUpdate(dt);

	if (pressed)
	{
		getResX().addForce(getOwner()->getDrag().x * strenghtX);
		getResY().addForce(getOwner()->getDrag().y * strenghtY);

		getOwner()->getRot().inverseMass = 0.45;
	}
	else
	{
		getResX().addForce(-getOwner()->getDrag().x * 0.1);

		getOwner()->getRot().inverseMass = 1.;
	}
	
	getResX().inverseMass = -0.45 + getOwner()->getAnimation("push").getPercentStep() * 0.2;



	getOwner()->getAnimation("arms").updateInRange(getOwner()->allModels, 1. * getResX().velocity);

	getOwner()->getAnimation("push").updateInRange(getOwner()->allModels, 1. * getResY().velocity);
	//getOwner()->getAnimation("push").updateInRange(getOwner()->allModels, 0.05 * getResY().velocity * getOwner()->getAnimation("arms").step);

	pressed = false;
}