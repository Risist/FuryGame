#include "EfectWeapon2hSword.h"
#include "EfectSwordMaterial.h"


EfectWeapon2hSword::EfectWeapon2hSword(sf::Sprite *_handSprite, sf::Sprite *_handSprite2)
	: EfectWeapon(_handSprite,"", "push"), handSprite2(_handSprite2)
	, dmgRatio(-0.125f), pushRatio(0.5f),
	clampDmg(-5., -0.01), clampPush(0.5, 8)
{
}


void EfectWeapon2hSword::onInit()
{
	EfectWeapon::onInit();

	getResX().resetVelocity = 0.85;
	getResX().inverseMass = -0.4f;

	getResY().resetVelocity = 0.85;
	getResY().inverseMass = -0.7f;

	//getOwner()->getPos().inverseMass *= 0.875;

	// weapon model;
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_s2h.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		addEfect(efModel = new EfectModel(stream, &middleHand, false, false));
	}
	
	getOwner()->allModels.push_back( &efModel->model);

	// animations
	
	getOwner()->addAnimation("sword", Animation("animation_s2h_sword.txt")); // wip
	getOwner()->addAnimation("push", Animation("animation_s2h_push.txt"));
	getOwner()->addAnimation( "arms", Animation("animation_s2h_arms.txt") );
	getOwner()->addAnimation("grab", Animation("animation_s2h_grab.txt"));
	{
		auto anim = getOwner()->getAnimation("grab");
		anim.update(getOwner()->allModels, anim.getStepMax() );
	}

	// efect After dealing damage
	auto efSword = new Game::MultiEfect;
	addEfect(efSword);

	efSword->addEfect(efDmg = new EfectDamageOnCollision(0.4, -0.5, 7.75));
	efSword->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efSword->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efSword->addEfect( new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efSword->addEfect(new EfectSwordMaterial(idResX, -1, 6, 0, &efModel->model));
	efSword->addEfect(new EfectSwordMaterial(idResY, -1, 3.5, 0, &efModel->model, 90));


	efSword->addEfect(efCollision = new EfectCollisionResponse(-2, 7.5, 12.5));

	// colliders
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-60, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-30, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(30, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(60, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(90, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(120, 0), 18), efSword, &efModel->model));


	getOwner()->layerCollider.collider.center.y = 0;
	getOwner()->layerCollider.collider.range = 335;
}

void EfectWeapon2hSword::onUpdate(float dt)
{
	
	

	//middleHand = *handSprite;

	middleHand.setPosition( Vector2D(handSprite->getPosition() + handSprite2->getPosition()) * 0.5 );
	
	Vector2D v1(0, 1); v1.rotate(handSprite->getRotation());
	Vector2D v2(0, 1); v2.rotate(handSprite2->getRotation());
	float angle = (v1 - v2).angle() - 90;
	middleHand.setRotation( angle);

	middleHand.setScale(Vector2D(handSprite->getScale() + handSprite2->getScale()) * 0.5);


	Game::MultiEfectNoInteract::onUpdate(dt);

	if (pressed)
	{
		getResX().addForce(getOwner()->getDrag().x * strenghtX);
		getResY().addForce(getOwner()->getDrag().y * strenghtY);

		getOwner()->getRot().inverseMass = 0.35;
	}
	else
	{
		getResX().addForce(-getOwner()->getDrag().x * 0.1);

		getOwner()->getRot().inverseMass = 1.;
	}

	float deltaRange = getOwner()->getAnimation("arms").getLenght() * 0.1;
	bool inRange = getOwner()->getAnimation("arms").inRange(
		getOwner()->getAnimation("arms").getStepMin() + deltaRange,
		getOwner()->getAnimation("arms").getStepMax() - deltaRange);
		//getOwner()->getAnimation("arms").inRange();

	float armsSpeed = 1;
	float swordSpeed = 1;
	float swordStep = getOwner()->getAnimation("sword").step, armsStep = getOwner()->getAnimation("arms").step;
	{

		float pushSpeed = 25;
		float armsSpeed = 0.01;
		float swordSpeed = 0.01;

		
		float difference = swordStep;// -armsStep*0.5;
		//cout << "diff " << diffirence << "\n";


		float force = pushSpeed * getResY().velocity / abs(difference);
		getOwner()->getAnimation("push").updateInRange(getOwner()->allModels, clamp(force,-10.f,10.f) );

		getOwner()->getAnimation("arms").updateInRange(getOwner()->allModels, armsSpeed * getResY().velocity * difference );
		getOwner()->getAnimation("sword").updateInRange(getOwner()->allModels, -swordSpeed  * getResY().velocity *difference);


	}
	getOwner()->getAnimation("arms").updateInRange(getOwner()->allModels, armsSpeed * (getResX().velocity ) );
	getOwner()->getAnimation("sword").updateInRange(getOwner()->allModels, swordSpeed *(getResX().velocity * (!inRange ? 1 : -0.1) ));

	pressed = false;

	
}

void EfectWeapon2hSword::wear()
{
	{
		auto anim = getOwner()->getAnimation("grab");
		anim.update(getOwner()->allModels, anim.getStepMax());
	}
}
void EfectWeapon2hSword::unwear()
{
	{
		auto anim = getOwner()->getAnimation("grab");
		anim.update(getOwner()->allModels, -anim.getStepMax());
	}

	getOwner()->getAnimation("sword").update(getOwner()->allModels, -getOwner()->getAnimation("sword").step);
	getOwner()->getAnimation("arms").update(getOwner()->allModels, -getOwner()->getAnimation("arms").step);
	getOwner()->getAnimation("push").update(getOwner()->allModels, -getOwner()->getAnimation("push").step);
}


void EfectWeapon2hSword::onDisplay(Camera& cam)
{
	EfectWeapon::onDisplay(cam);
}