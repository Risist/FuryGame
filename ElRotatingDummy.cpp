#include "ElRotatingDummy.h"
#include "GameMultiEfectNoInteract.h"

#include "EfectRotateOnCollision.h"
extern Game::World world;

namespace El
{

	RotatingDummy::RotatingDummy(Game::Object *_toFollow)
		: respawnTimer(10), toFollow(_toFollow)
	{
	}

	void RotatingDummy::onInit()
	{
		Game::Object::onInit();

		addEfect(efModel = new EfectModel("model_dummy_arm.txt"));

		auto ef = new Game::MultiEfectNoInteract;
		addEfect(ef);


		if (toFollow != nullptr)
		{
			auto efFollow = addEfect(new EfectFollowAim(toFollow, 20, 5, 0.75f));
			addEfect(new EfectUseUnderCondition(efFollow, new Allow::Timer(Control::Timer(20, false))));
		}
		// body
		{
			auto efBody = new Game::MultiEfect();
			ef->addEfect(efBody);

			efBody->addEfect(new EfectCollisionResponse(-6, 10, 100));
			efBody->addEfect(new EfectMaterial(pos, EfectMaterial::v2, this, 1));
			efBody->addEfect(new EfectMaterial(hp, EfectMaterial::f, this, 0.725));

			layerCollider = ColliderInfo(CircleCollider(Vector2D(), 200), nullptr, &efModel->model);
			addCollider(ColliderInfo(CircleCollider(Vector2D(), 75), efBody, &efModel->model));
		}
		// Arm
		{
			auto efArm = new Game::MultiEfect();
			ef->addEfect(efArm);
			efArm->addEfect(new EfectCollisionResponse(-4, 10, 100));

			// materials
			efArm->addEfect(new EfectMaterial(pos, EfectMaterial::v2, this, 0.1));
			efArm->addEfect(new EfectMaterial(hp, EfectMaterial::f, this, 0.125));

			efArm->addEfect(new EfectRotateOnCollision(1.75, &efModel->model));
			efArm->addEfect( new EfectDamageOnCollision(4, -5, 12));

			//addCollider(ColliderInfo(CircleCollider(Vector2D(0, 100), 25), efArm, &efModel->model));
			//addCollider(ColliderInfo(CircleCollider(Vector2D(0, 150), 25), efArm, &efModel->model));
			//addCollider(ColliderInfo(CircleCollider(Vector2D(0, 200), 25), efArm, &efModel->model));

			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 60), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 80), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 100), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 120), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 140), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 160), 13), efArm, &efModel->model));
			addCollider(ColliderInfo(CircleCollider(Vector2D(0, 180), 13), efArm, &efModel->model));
		}
		// other basic efects

		addEfect(new EfectDebugCollider(sf::Keyboard::Z, Color(200, 200, 200, 100)));
		addEfect(new EfectCheckForCollision(&world));
		

		getHp().inverseMass = 0.25f;
		getPos().inverseMass = 0.25f;
		getRot().inverseMass = 1.25;
		getRot().resetVelocity = 0.99;
	}

	void RotatingDummy::onUpdate(float dt)
	{
		Game::Object::onUpdate(dt);
		
		if (toFollow == nullptr)
		{
			auto toLock = getPosC().position - lockedPosition;
			onPush(-toLock * 0.05);
		}
		//onSwing(0.5);
	}

	void RotatingDummy::onDisplay(Camera& cam)
	{
		Game::Object::onDisplay(cam);
		float state = 1;

		state *= sqrt(getHpC().position / 100);

		state *= 150;
		state += 105;
		efModel->model.setColor(Color(state, state, state, state));
	}
	void RotatingDummy::onInteract(float force, size_t resId, Game::Object* causer)
	{
		Game::Object::onInteract(force, resId, causer);
		if (resId == hp)
			respawnTimer.restart();
	}
	bool RotatingDummy::onDeath()
	{
		//if (respawnTimer.isReady())
			//getHp().position = 100;
		return false;
	}
}

