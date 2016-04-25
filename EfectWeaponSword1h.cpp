#include "EfectWeaponSword1h.h"
#include "EfectSwordMaterial.h"
#include "EfectRotateOnCollision.h"

EfectWeaponSword1h::EfectWeaponSword1h( sf::Sprite* _handSprite)
	: EfectWeapon( _handSprite, "rightX", "rightY")
	, dmgRatio(-0.175f), pushRatio(0.25f),
	clampDmg(-5., -0.01), clampPush(0.5, 3),
	changeRotation(0.6f)
{
}

EfectRotateOnCollision *efRot;

void EfectWeaponSword1h::onInit()
{
	EfectWeapon::onInit();

	idColiderMin = getOwner()->colliders.size();

	wear();
	//getOwner()->getPos().inverseMass *= 0.975;

	// weapon model;
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_s1h.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		addEfect(efModel = new EfectModel(stream, handSprite, false, false));
	}
	

	// Animations

	getOwner()->addAnimation(animCodeX, Animation("animation_s1h_cross.txt"));
	getOwner()->addAnimation(animCodeY, Animation("animation_s1h_push.txt"));

	// efect After dealing damage
	auto efSword = new Game::MultiEfect;
	addEfect(efSword);

	efSword->addEfect(efDmg = new EfectDamageOnCollision(0.3, -0.4, 3.));
	efSword->addEfect(new EfectUseUnderCondition(efDmg, new Allow::Timer(Control::Timer(0.0125))));
	efSword->addEfect(new EfectMaterial( pos, EfectMaterial::v2, getOwner(), 0.15));
	efSword->addEfect(efRot = new EfectRotateOnCollision(0.35, handSprite));
	//efSword->addEfect(new EfectSwordMaterial(idResX,idResY, 3.5, 0, &efModel->model) );
	efSword->addEfect(new EfectSwordMaterial(idResX, idResY, 7., 5., &efModel->model));

	strenghtX = 1.5;


	efSword->addEfect(efCollision = new EfectCollisionResponse(-5, 7.5,12.5));

	// colliders
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-30, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(30, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(60, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(90, 0), 18), efSword, &efModel->model));
	getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(120, 0), 18), efSword, &efModel->model));

	idColiderMax = getOwner()->colliders.size();

	getOwner()->layerCollider.collider.center.y = 0;
	getOwner()->layerCollider.collider.range = 285;
}

void EfectWeaponSword1h::wear()
{
	//resX
	getResX().resetVelocity = 0.85;
	getResX().inverseMass = -0.35f;

	//resY
	getResY().resetVelocity = 0.85;
	getResY().inverseMass = -0.6f;
}
void EfectWeaponSword1h::unwear()
{
	getOwner()->getAnimation(animCodeX).update(getOwner()->allModels, -getOwner()->getAnimation(animCodeX).step);
	getOwner()->getAnimation(animCodeY).update(getOwner()->allModels, -getOwner()->getAnimation(animCodeY).step);
}

void EfectWeaponSword1h::onUpdate(float dt)
{
	EfectWeapon::onUpdate(dt);
}

void EfectWeaponSword1h::onDisplay(Camera& cam)
{
	EfectWeapon::onDisplay(cam);



}