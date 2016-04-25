#include "ElDummy.h"
#include "GamePlayer.h"
#include <sstream>

extern Game::World world;
extern Camera cam;

namespace El
{

	Dummy::Dummy()
		: respawnTimer(25.), alive(true), deathTimer(1.f)
	{
	}

	void Dummy::onInit()
	{
		Game::Object::onInit();

		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_dummy.txt", constructionScript, model_loaded);

		stringstream stream(constructionScript);
		addEfect(efModel = new EfectModel(stream) );

		layerCollider = ColliderInfo(CircleCollider(Vector2D(), 75), this, &efModel->model);
		addCollider( layerCollider);
		

		addEfect(new EfectDamageOnCollision(-1., -0.1, 1) );
		addEfect(new EfectDebugCollider(sf::Keyboard::Z, Color(200, 200, 200, 100)));
		addEfect(new EfectCollisionResponse(0, 10, 1000));
		//addEfect(new EfectCheckForCollision(&world));
		//addEfect(new EfectSpringJoint());

		getHp().inverseMass = 0.5f;
		getPos().inverseMass = 0.1f;

		getHp().position = 40;
		//getHp().resetVelocity = 0;

		//getHp().inverseMass = 1.f;
		//getPos().inverseMass = 1.0f;

	}

	void Dummy::onUpdate(float dt)
	{
		Game::Object::onUpdate(dt);

		auto toLock = getPosC().position - lockedPosition;
		//onPush( -toLock * 0.125);
	}

	void Dummy::onDisplay(Camera& cam)
	{
		Game::Object::onDisplay(cam);
		float state = 1;
		
		state *=  sqrt(getHpC().position / 50);
		
		state *= 150;
		state += 105;
		efModel->model.setColor( Color(state,state,state, state));
	}
	void Dummy::onInteract(float force, size_t resId, Game::Object* causer)
	{
		Game::Object::onInteract(force, resId, causer);
		if (resId == hp)
			respawnTimer.restart();
	}
	bool Dummy::onDeath()
	{

		static const float playerDistance = 600;


		if (alive)
		{
			//getHp().position = 100;
			for each (auto it in world)
				if (it != nullptr && it != this && it->isAlive() && (it->getPosC().position - getPosC().position).getLenghtSq() < playerDistance * playerDistance)
				{
					if (dynamic_cast<Game::Player*>(it) != nullptr )
					{
						cam.setAlpha(cam.getAlpha() * 0.9);
					}
					it->getHp().addForce(3.5);
				}

			
			alive = false;
			deathTimer.restart();
		}
		return false;
		return deathTimer.isReady();
	}
}
