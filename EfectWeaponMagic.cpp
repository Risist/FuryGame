#include "EfectWeaponMagic.h"
#include "EfectSwordMaterial.h"


EfectWeaponMagic::EfectWeaponMagic(sf::Sprite *handSprite, sf::Sprite *_handSprite2)
	: EfectWeapon(handSprite, "x", "y"), handSprite2(_handSprite2)
{
}

void EfectWeaponMagic::onInit()
{
	EfectWeapon::onInit();

	getOwner()->addAnimation("x", Animation("animation_magic_arms.txt"));
	getOwner()->addAnimation("y", Animation("animation_magic_grab.txt"));

	getOwner()->getAnimation("y").update(getOwner()->allModels, getOwner()->getAnimation("y").getStepMin() );

	addEfect(new EfectParticle("particleMagic.txt", 75, 10, 1, 0, nullptr, &middleHand));


	auto efSpell = new Game::MultiEfect;
	addEfect(efSpell);

	//efSpell->addEfect(efDmg = new EfectDamageOnCollision(0.4, -0.5, 7.75));
	//efSpell->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efSpell->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.15));
	efSpell->addEfect(new EfectRotateOnCollision(0.35, handSprite));

	efSpell->addEfect(new EfectSwordMaterial(idResX, -1, 1, 0, &middleHand));
	efSpell->addEfect(new EfectSwordMaterial(idResY, -1, 1, 0, &middleHand, 90));

	efSpell->addEfect( new EfectCollisionResponse(20, 7.5, 12.5));

	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(), 35), efSpell, &middleHand));

	getResY().inverseMass = -0.75;
	getResY().resetVelocity = 0.8;
}

void EfectWeaponMagic::onUpdate(float dt)
{

	
	Vector2D v1(0, 1); v1.rotate(handSprite->getRotation());
	Vector2D v2(0, 1); v2.rotate(handSprite2->getRotation());
	float angle = (v1 - v2).angle() - 90;
	middleHand.setRotation(angle);

	Vector2D offset = Vector2D(0, 40).getRotated(angle);
	//cout << "angle " << angle << "\n";
	//offset.x = abs(offset.x);
	//offset.y = abs(offset.y);
	middleHand.setPosition(Vector2D(handSprite->getPosition() + handSprite2->getPosition()) * 0.5 
		+  offset);


	middleHand.setScale(Vector2D(handSprite->getScale() + handSprite2->getScale()) * 0.5);

	Game::MultiEfectNoInteract::onUpdate(dt);

	if (pressed)
	{
		getResX().addForce(getOwner()->getDrag().x * strenghtX);
		getResY().addForce(getOwner()->getDrag().y * strenghtY);
	}

	float armsSteap = getOwner()->getAnimation("x").step;

	float forceY = 1 * getResY().velocity;// / abs(armsSteap);
	float forceX = 1 * getResX().velocity ;

	getOwner()->getAnimation("x").updateInRange(getOwner()->allModels, forceX);
	getOwner()->getAnimation("y").updateInRange(getOwner()->allModels, clamp(forceY, -10.f, 10.f));



	pressed = false;
}
