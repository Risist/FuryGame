#include "EfectWeaponShield.h"
#include "EfectRotateOnCollision.h"
#include "EfectSwordMaterial.h"

EfectWeaponShield::EfectWeaponShield(sf::Sprite* handSprite)
	: EfectWeapon(handSprite, "leftX", "leftY")
{
}

void EfectWeaponShield::onInit()
{
	EfectWeapon::onInit();
	idColiderMin = getOwner()->colliders.size();
	getResX().inverseMass = 0.5;

	//getOwner()->getPos().inverseMass *= 0.9;

	// weapon model;
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_shl.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		getOwner()->addEfect(efModel = new EfectModel(stream, handSprite, false, false));
	}
	getOwner()->allModels.push_back(&efModel->model);

	// Animations
	getOwner()->addAnimation(animCodeX, Animation("animation_shl_cross.txt"));
	getOwner()->addAnimation(animCodeY, Animation("animation_shl_push.txt"));

	//shield Colliders
	auto efShield = new Game::MultiEfect;
	addEfect(efShield);

	efShield->addEfect(new EfectMaterial(pos, EfectMaterial::v2, getOwner(), 0.9));
	//efShield->addEfect(new EfectMaterial(hp, EfectMaterial::f, getOwner(), 0.075));
	efShield->addEfect(new EfectRotateOnCollision(0.65, handSprite, 90));
	efShield->addEfect(new EfectSwordMaterial(idResX, idResY, 5.75, 3.5, &efModel->model,-90));

	efShield->addEfect(new EfectCollisionResponse( 30, 12.5, 100));


	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 25), 45), efShield, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -10), 55), efShield, &efModel->model));

	idColiderMax = getOwner()->colliders.size();
}

void EfectWeaponShield::onUpdate(float dt)
{
	EfectWeapon::onUpdate(dt);
	

}
