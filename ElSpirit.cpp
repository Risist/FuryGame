#include "ElSpirit.h"

extern Game::World world;

namespace El
{

	Spirit::Spirit() : tNewAim(0.5f)
	{

	}

	void Spirit::onInit()
	{
		Game::Object::onInit();

		static bool model_loaded = false;
		static string constructionScript;

		loadScript("model_spirit.txt", constructionScript, model_loaded);

		stringstream stream(constructionScript);
		addEfect( efModel = new EfectModel(stream) );

		layerCollider = ColliderInfo(CircleCollider(Vector2D(), 50), this, &efModel->model);
		addCollider( layerCollider);
		addEfect( new EfectDebugCollider(sf::Keyboard::Z, Color(200, 200, 200, 100)));

		addEfect(efFollowAim = new EfectFollowAim(nullptr, 2.5, 0, tNewAim.time_wait, Vector2D( 0, 150) ));
		addEfect( new EfectCollisionResponse(5., 0.0125, 20));
		//addEfect(new EfectCheckForCollision(&world));
		addEfect(efDamageOnCollision = new EfectDamageOnCollision(0, -1, 10));


		getPos().inverseMass = 1.;
		getPos().resetVelocity = 0.85;
		getHp().inverseMass = 1.5;


	}
	void Spirit::onDisplay(Camera& cam)
	{
		Game::Object::onDisplay(cam);
		float state = 1;

		state *= sqrt(getHpC().position / 100);

		state *= 150;
		state += 105;
		efModel->model.setColor(Color(state, state, state, state));
	}
	void Spirit::onUpdate(float dt)
	{
		Game::Object::onUpdate(dt);
		findAim();
		onDamage(-0.025);

		//cout << "hp: " << getHp().force << "\n";
	}

	void Spirit::findAim()
	{
		if (tNewAim.isReady())
		{

			// main contradictor
			static Allow::NotEqual *notEqual = nullptr;
			static Evaluate::Distance *ifDistance = nullptr;
			static Evaluate::Distance *distance1 = nullptr, *distance2 = nullptr;

			static Evaluate::Operator evaluate(
			{
				new Evaluate::Condition(new Evaluate::Const(1), new Evaluate::Const(-1),
				new Allow::Operator({ notEqual = new Allow::NotEqual(this), new Allow::Class<Game::Competitor>, }
				, Allow::Operator::And)),

				new Evaluate::RandRange(new Evaluate::Const(1 / 1.25), new Evaluate::Const(1.25)),

				distance1 = new Evaluate::Distance(this, Vector2D(), Position, Evaluate::Distance::LenghtSq),
				distance2 = new Evaluate::Distance(this, Vector2D(), Position, Evaluate::Distance::LenghtSq),
				new Evaluate::Stat_f(hp),
			},
			Evaluate::Operator::division
			);

			// flying references
			if (notEqual != nullptr)
				notEqual->toCompare = this;
			if (ifDistance != nullptr)
				ifDistance->toCheck = this;
			if (distance1 != nullptr)
				distance1->toCheck = this;

			efFollowAim->aimObject = Game::getBest(world, &evaluate, 0);

			if (notEqual != nullptr)
				notEqual->toCompare = nullptr;
			if (ifDistance != nullptr)
				ifDistance->toCheck = nullptr;
			if (distance1 != nullptr)
				distance1->toCheck = nullptr;

		}
	}
}
