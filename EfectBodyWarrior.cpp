#include "EfectBodyWarrior.h"

#include "EfectWeaponSword1h.h"
#include "EfectWeaponShield.h"
#include "EfectJumpMovement.h"

#include "Efect2WeaponMaterial.h"
#include "EfectWeaponSpear.h"
#include "EfectWeapon2hSword.h"
#include "EfectWeapon2hAxe.h"
#include "EfectWeaponMagic.h"

extern Game::World world;

EfectBodyWarrior::EfectBodyWarrior(size_t _idWeapon)
	: efWeaponLeft(nullptr), efWeaponRight(nullptr), idWeapon(_idWeapon), alive(true)
{
}

void EfectBodyWarrior::loadModels()
{
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_shiv_body.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		getOwner()->initEfect(efBody = new EfectModel(stream, nullptr, false, false, false));
	}
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_shiv_arm_left.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		getOwner()->initEfect(efArmLeft = new EfectModel(stream, &efBody->model, false, false, false));
	}
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_shiv_arm_right.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		getOwner()->initEfect(efArmRight = new EfectModel(stream, &efBody->model, false, false, false));
	}
	{
		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_shiv_head.txt", constructionScript, model_loaded);
		static stringstream stream;
		stream.str(constructionScript);
		getOwner()->initEfect(efHead = new EfectModel(stream, &efBody->model, false, false));
	}
	
	/* worse version*/
	//getOwner()->initEfect(efBody = new EfectModel("model_shiv_body.txt", nullptr, false, false, false));
	//getOwner()->initEfect(efArmLeft = new EfectModel("model_shiv_arm_left.txt", &efBody->model, false, false, false));
	//getOwner()->initEfect(efArmRight = new EfectModel("model_shiv_arm_right.txt", &efBody->model, false, false, false));
	//getOwner()->initEfect(efHead = new EfectModel("model_shiv_head.txt", &efBody->model, false, false));
}

void EfectBodyWarrior::onInit()
{
	Game::MultiEfectNoInteract::onInit();


	{ // model definition

		loadModels();
		
		getOwner()->initAllModels(efBody->model);
		getOwner()->initAllModels(efArmRight->model);
		getOwner()->initAllModels(efArmLeft->model);
		getOwner()->initAllModels(efHead->model);

		getOwner()->layerCollider.connectedTo = &efBody->model;

		getOwner()->addEfect(new EfectUpdateModel(&efBody->model));
		getOwner()->addEfect(new EfectUpdateModel(&efArmLeft->model, &efBody->model, false, false));
		getOwner()->addEfect(new EfectUpdateModel(&efArmRight->model, &efBody->model, false, false));
		{
			// right arm
			if (idWeapon == 0 || idWeapon == 1)
				getOwner()->addEfect(efWeaponLeft = efWeaponRight = new EfectWeaponSword1h(getOwner()->allModels[3]));
			else if (idWeapon == 2)
				getOwner()->addEfect(efWeaponLeft = efWeaponRight = new EfectWeapon2hSword(getOwner()->allModels[3], getOwner()->allModels[5]));
			else if ( idWeapon == 3)
				getOwner()->addEfect(efWeaponLeft = efWeaponRight = new EfectWeaponSpear(getOwner()->allModels[3], getOwner()->allModels[5]));
			else if (idWeapon == 4)
				getOwner()->addEfect(efWeaponLeft = efWeaponRight = new EfectWeapon2hAxe(getOwner()->allModels[3], getOwner()->allModels[5]));
			else if (idWeapon == 5)
			{
				getOwner()->addEfect(efWeaponLeft = efWeaponRight = new EfectWeaponMagic(getOwner()->allModels[3], getOwner()->allModels[5]));
			}

			getOwner()->addEfectNoInit(efArmRight);
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(5, 15), 15), getOwner(), &efArmRight->model));

			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -43), 17), getOwner(), efArmRight->model.childDown));
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -13), 17), getOwner(), efArmRight->model.childDown));
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 17), 17), getOwner(), efArmRight->model.childDown));


			// left arm
			getOwner()->addEfectNoInit(efArmLeft);
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(-5, 15), 15), getOwner(), &efArmLeft->model));

			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -43), 17), getOwner(), efArmLeft->model.childDown));
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -13), 17), getOwner(), efArmLeft->model.childDown));
			//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 17), 17), getOwner(), efArmLeft->model.childDown));

			if (idWeapon == 1)
				getOwner()->addEfect(efWeaponLeft = new EfectWeaponShield(getOwner()->allModels[5]));

		}
		getOwner()->addEfectNoInit(efBody);
		getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 0), 45), getOwner(), &efBody->model));
		//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 0), 45), getOwner(), &efBody->model));

		

		
		// head
		getOwner()->addEfectNoInit(efHead);
		//getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, -5), 25), getOwner(), &efHead->model));
		getOwner()->addCollider(ColliderInfo(CircleCollider(Vector2D(0, 25), 20), getOwner(), &efHead->model));

	}

	getOwner()->addEfect(new EfectCollisionResponse(10, 10, 100));
	getOwner()->addEfect(new EfectCheckForCollision(&world));

	addEfect(new EfectTppMovement(4.5, 0.5));

	size_t id = getOwner()->addResource(Resource<float>());
	getOwner()->getResource_f(id).resetVelocity = 0.99;

	addEfect(new EfectJumpMovement(6.5, "jump", id, -4., 1., 0.125, 0.25 ));

	addEfect(new EfectMaxHealth(100, EfectMaxHealth::dmgChange, 1));


	//getOwner()->getHp().inverseMass = 0.75;
	//getOwner()->getPos().inverseMass *= 1.1;
	
}

void EfectBodyWarrior::onUpdate(float dt)
{
	Game::MultiEfectNoInteract::onUpdate(dt);

	if (efWeaponLeft != nullptr && getOwner()->isPressed("s1"))
	{
		efWeaponLeft->press();
		getOwner()->getRot().inverseMass = 0.45;
	}
	else if (efWeaponRight != nullptr && getOwner()->isPressed("s2"))
	{
		efWeaponRight->press();
		getOwner()->getRot().inverseMass = 0.45;
	}


	if (!getOwner()->isPressed("s2") && !getOwner()->isPressed("s1"))
	{
		getOwner()->getRot().inverseMass = 1.;
		getOwner()->getRot().resetVelocity = 0.7;
	}
}

void EfectBodyWarrior::onDisplay(Camera&cam)
{
	Game::MultiEfectNoInteract::onDisplay(cam);

	
}


bool EfectBodyWarrior::onDeath()
{
	if (alive)
	{
		//getOwner()->getHp().position = 75;
		alive = false;
	}
	else
	{

	}
	return false;// getOwner()->getHpC().position < 50;
}