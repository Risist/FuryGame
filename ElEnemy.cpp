#include "ElEnemy.h"
#include "EfectBotRandomPress.h"
#include "EfectResetInput.h"
#include "GamePlayer.h"


extern Game::World world;
extern Camera cam;

extern Vector2D positionOfMap;
extern Vector2D mapRange;

namespace El
{
	Enemy::Enemy(size_t _idWeapon, El::Player *_player)
		: aim(nullptr), tNewAim(0.5),
		idWeapon(_idWeapon), alive(true), deathTimer(2.f),
		player(_player), stayOnTheMap(nullptr)
	{
	}

	void Enemy::onInit()
	{
		Game::Object::onInit();

		addEfect(new EfectCircleSign(
			60, Color(150, 0, 0), Color(0, 0, 0),
			nullptr, 100,
			new Evaluate::Stat_f(Game::Event::pos, Evaluate::Stat_f::position)
			));

		addEfect( efBodyWarrior = new EfectBodyWarrior(idWeapon) );

		addEfect(new EfectDebugCollider(sf::Keyboard::Z, Color(200, 200, 200, 100)));
		addEfect(new EfectResetInput());


		aimsToAvoid.resize(3, nullptr);

		

		// avoid aims test
		/**auto actionAvoidObstacle = new ActionSet;

		actionAvoidObstacle->initAfterActions(
		{
			new ActionMoveTo(&aimsToAvoid[0], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),
			new ActionMoveTo(&aimsToAvoid[1], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),
			new ActionMoveTo(&aimsToAvoid[2], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),

			new ActionLookAt(&aim, 50, 0.25),
			new ActionMoveTo(&aim, 20, Vector2D(-100, 0), Vector2D(1.1, 1.1), true, false),
			stayOnTheMapOfensive = new ActionMoveTo(positionOfMap, Vector2D(0, mapRange.y - 150), Vector2D(2.5, 400.1)),

		});

		efMind->initActions({ actionAvoidObstacle });
		efMind->setActualProcessedAction(actionAvoidObstacle);/**/

		//ofensive & defensive states ai
		/**auto actionOfensive = new ActionSet;
		auto actionDefensive = new ActionSet;

		actionOfensive->initAfterActions(
		{
			//new ActionMoveTo(&aimsToAvoid[0], 0, Vector2D(150, 10000), Vector2D(5000, 0), false, true),
			//new ActionMoveTo(&aimsToAvoid[1], 0, Vector2D(150, 10000), Vector2D(5000, 0), false, true),
			//new ActionMoveTo(&aimsToAvoid[2], 0, Vector2D(150, 10000), Vector2D(5000, 0), false, true),

			new ActionLookAt(&aim, 20, 0.25),
			new ActionMoveTo(&aim, 20, Vector2D(-100, 0), Vector2D(1.1, 1.1), true, false),
			stayOnTheMapOfensive = new ActionMoveTo(positionOfMap, Vector2D(0, mapRange.y - 150), Vector2D(2.5, 400.1)),

			new ActionRandomPress("s1", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
			new ActionRandomPress("s2", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
			new ActionRandomPress("jump", randRange(0.05, 0.25), randRange(0.25, 0.6), randRange(0.125, 0.5), 1.05),
			new ActionRandomDrag(&drag.x, randRange(-10, -3), randRange(3, 10)),
			new ActionRandomDrag(&drag.y, randRange(-3, -0.1), randRange(3, 10)),


			// random movement
			new ActionRandomPress("up", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),
			new ActionRandomPress("down", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),
			new ActionRandomPress("left", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),
			new ActionRandomPress("right", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),

			new ActionAllow(new Allow::Timer(Control::Timer(0.05)), 
			{ 
				make_pair(actionOfensive, 10),
				make_pair(actionDefensive, 5),
			}),
		});

		actionDefensive->initAfterActions(
		{
			new ActionMoveTo(&aimsToAvoid[0], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),
			new ActionMoveTo(&aimsToAvoid[1], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),
			new ActionMoveTo(&aimsToAvoid[2], 0, Vector2D(150, 10000), Vector2D(5, 5), false, true),


			new ActionLookAt(&aim, 20, 0.25),
			new ActionMoveTo(&aim, 20, Vector2D(15, 150), Vector2D(1.1, 1.1), false, true),
			stayOnTheMapDefensive = new ActionMoveTo(positionOfMap, Vector2D(0, mapRange.y - 150), Vector2D(2.5, 400.1)),

			// keys
			new ActionRandomPress("s1", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
			new ActionRandomPress("s2", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
			new ActionRandomPress("jump", randRange(0.05, 0.25), randRange(0.25, 0.6), randRange(0.125, 0.5), 1.05),
			new ActionRandomDrag(&drag.x, randRange(-10, -3), randRange(3, 10)),
			new ActionRandomDrag(&drag.y, randRange(-10, -3), randRange(0.1, 3)),


			// random movement
			new ActionRandomPress("up", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),
			new ActionRandomPress("down", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25),
			new ActionRandomPress("left", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.6, 0.8), 2.5),
			new ActionRandomPress("right", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.6, 0.8), 2.5),


			new ActionAllow(new Allow::Timer(Control::Timer(0.05)),
			{
				make_pair(actionOfensive, 10),
				make_pair(actionDefensive, 5),
				
			}),
		});
		efMind->initActions({ actionOfensive, actionDefensive });
		efMind->setActualProcessedAction(actionDefensive);/**/

		addStates();
		
		

		addEfect(new EfectCombineAxes("down", "up"));
		addEfect(new EfectCombineAxes("left", "right"));
		addEfect(new EfectCombineAxes("s1", "s2"));

		/*addEfect(new EfectLockInput("up", 0.2));
		addEfect(new EfectLockInput("down", 0.2));
		addEfect(new EfectLockInput("left", 0.2));
		addEfect(new EfectLockInput("right", 0.2));*/
		// constant parametrs

		getRot().resetVelocity = 0.65;
		getPos().resetVelocity = 0.65;
	}
	void Enemy::addStates()
	{
		{
			// actions that are common to each state
			auto efConstant = new EfectAction();
			addEfect(efConstant);
			auto acConstant = new ActionSet();
			acConstant->initAfterActions(
			{
				// avoid obstacles
				new ActionMoveTo(&aimsToAvoid[0], 0, Vector2D(100, 1000), Vector2D(1, 0), false, true),
				new ActionMoveTo(&aimsToAvoid[1], 0, Vector2D(150, 1000), Vector2D(0.9, 0), false, true),
				new ActionMoveTo(&aimsToAvoid[2], 0, Vector2D(150, 1000), Vector2D(0.8, 0), false, true),

				// moveToPlayer
				new ActionMoveTo( (Game::Object**)&player, 0, Vector2D(0, 600), Vector2D(0, 0.0001), false, true),

				// stay on the map
				stayOnTheMap = new ActionMoveTo(positionOfMap, Vector2D(0, mapRange.y - 150), Vector2D(2.5, 400.1)),

				new ActionRandomPress("up", 0, 0.1, randRange(0.5, 0.75), 2.25),
				new ActionRandomPress("down", 0, 0.1, randRange(0.5, 0.75), 2.25),
				new ActionRandomPress("left", 0, 0.1, randRange(0.6, 0.8), 2.5),
				new ActionRandomPress("right", 0, 0.1, randRange(0.6, 0.8), 2.5),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acConstant, 1),
				}),

			});
			efConstant->initActions({ acConstant });
			efConstant->setActualProcessedAction(acConstant);
		}
		{
			// follow aim
			auto efFollow = new EfectAction();
			addEfect(efFollow);

			auto acPursuit = new ActionSet;
			auto acFlee = new ActionSet;

			acPursuit->initAfterActions(
			{
				new ActionLookAt(&aim, 20, 0.25),
				new ActionMoveTo(&aim, 20, Vector2D(-50, 50), Vector2D(1, 1), true),

				new ActionRandomPress("jump", 0, 0.1, randRange(0.125, 0.5), 1.75),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acFlee, 1),
					make_pair(acPursuit, 2.5),
				}),
			});

			acFlee->initAfterActions(
			{
				new ActionLookAt(&aim, 40, 0.25),
				new ActionMoveTo(&aim, 40, Vector2D(100, 150), Vector2D(1, 1), false, true),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acFlee, 5),
					make_pair(acPursuit, 1),
				}),

			});

			efFollow->initActions({ acPursuit, acFlee });
			efFollow->setActualProcessedAction(acFlee);
		}
		{
			// moving weapon
			auto efMind = new EfectAction();
			addEfect(efMind);

			auto acSwingWeaponLeft = new ActionSet;
			auto acSwingWeaponRight = new ActionSet;
			auto acPush = new ActionSet;
			auto acBack = new ActionSet;
			auto acNothing = new ActionSet;

			acSwingWeaponLeft->initAfterActions({
				new ActionRandomDrag(&drag.x, randRange(3, 1), randRange(3, 10)),
				//new ActionRandomDrag(&drag.y, randRange(-10, -3), randRange(0.1, 3)),

				new ActionRandomPress("s1", 0, 0.1, randRange(0.5, 0.75), 5.25),
				new ActionRandomPress("s2", 0, 0.1, randRange(0.5, 0.75), 5.25),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acSwingWeaponLeft, 1),
					make_pair(acSwingWeaponRight, 10),
					make_pair(acPush, 1),
				}),
			});

			acSwingWeaponRight->initAfterActions({
				new ActionRandomDrag(&drag.x, randRange(-10, -3), randRange(1, 3)),
				//new ActionRandomDrag(&drag.y, randRange(-10, -3), randRange(0.1, 3)),

				new ActionRandomPress("s1", 0, 0.1, randRange(0.5, 0.75), 5.25),
				new ActionRandomPress("s2", 0, 0.1, randRange(0.5, 0.75), 5.25),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acSwingWeaponLeft, 1),
					make_pair(acSwingWeaponRight, 1),
					make_pair(acPush, 1),
					make_pair(acBack, 0.5),
					make_pair(acNothing, 0.1),
				}),
			});

			acPush->initAfterActions({
				//new ActionRandomDrag(&drag.x, randRange(3, 1), randRange(3, 10)),
				new ActionRandomDrag(&drag.y, randRange(-10, -3), randRange(1, 3)),

				new ActionRandomPress("s1", 0, 0.1, randRange(0.5, 0.75), 5.25),
				new ActionRandomPress("s2", 0, 0.1, randRange(0.5, 0.75), 5.25),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acSwingWeaponLeft, 1),
					make_pair(acSwingWeaponRight, 1),
					make_pair(acPush, 1),
					make_pair(acBack, 0.5),
					make_pair(acNothing, 0.1),
				}),
			});
			acBack->initAfterActions({
				//new ActionRandomDrag(&drag.x, randRange(3, 1), randRange(3, 10)),
				new ActionRandomDrag(&drag.y, randRange(3, 1), randRange(3, 10)),

				new ActionRandomPress("s1", 0, 0.1, randRange(0.5, 0.75), 5.25),
				new ActionRandomPress("s2", 0, 0.1, randRange(0.5, 0.75), 5.25),

				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acSwingWeaponLeft, 1),
					make_pair(acSwingWeaponRight, 1),
					make_pair(acPush, 1),
					make_pair(acBack, 0.5),
					make_pair(acNothing, 0.1),
				}),
			});

			acNothing->initAfterActions({
				
				new ActionAllow(new Allow::Timer(Control::Timer(0.1)),
				{
					make_pair(acSwingWeaponLeft, 1),
					make_pair(acSwingWeaponRight, 1),
					make_pair(acPush, 1),
					make_pair(acBack, 0.5),
					make_pair(acNothing, 1),
				}),
			});

			efMind->initActions({ acPush, acBack, acSwingWeaponLeft, acSwingWeaponRight });
			efMind->setActualProcessedAction(acNothing);
		}
	}

	void Enemy::onUpdate(float dt)
	{
		
		Game::Competitor::onUpdate(dt);
		findAim();

		if (stayOnTheMap != nullptr)
			stayOnTheMap->radius = Vector2D(0, mapRange.y - 150);

		Vector2D drag = getDrag();
		//drag.truncate(5.);
		drag.truncate(7.5);
		setDrag( drag );
		
	}
	

	void Enemy::findAim()
	{
		// bot's field of view propertites
		static const float viewRange = 550;
		static const Vector2D viewOffset = Vector2D(0, -250);

		// bot's follow propertites
		static const float followMin = -50, 
						followMax = 200;


		/**/{ // debug
			CircleCollider cClose(getPosC().position, followMin), cGood(getPosC().position, followMax),
				cView(getPosC().position + viewOffset.getRotated(getRotC().position), viewRange);
			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				cClose.display(cam, Color(100, 250, 100, 75));
				cGood.display(cam, Color(250, 250, 100, 75));
				cView.display(cam, Color(150, 150, 150, 125));
			}
		}/**/

		// find new aim
		if (tNewAim.isReady())
		{
			{
				// main contradictor
				static Allow::NotEqual *notEqual = nullptr;
				static Evaluate::Distance *ifDistance = nullptr;
				static Evaluate::Distance *distance1 = nullptr, *distance2 = nullptr;

				static Evaluate::Operator evaluate(
				{
					new Evaluate::Condition(new Evaluate::Const(1), new Evaluate::Const(-1),
					new Allow::Operator({ notEqual = new Allow::NotEqual(this), new Allow::Class<Game::Competitor>,
					// field of view
					new Allow::StatInRange(ifDistance = new Evaluate::Distance(this, viewOffset), nullptr, new Evaluate::Const(viewRange)) }, Allow::Operator::And)),

					new Evaluate::Condition(new Evaluate::Const(1), new Evaluate::Const(1.25), new Allow::Class<Game::Player>),
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

				aim = Game::getBest(world, &evaluate, 0);

				if (notEqual != nullptr)
					notEqual->toCompare = nullptr;
				if (ifDistance != nullptr)
					ifDistance->toCheck = nullptr;
				if (distance1 != nullptr)
					distance1->toCheck = nullptr;

			}
			// objects to avoid
			{
				static Allow::NotEqual *notEqual = nullptr;
				static Evaluate::Distance *ifDistance = nullptr;
				static Evaluate::Distance *distance1 = nullptr, *distance2 = nullptr;

				static Evaluate::Operator evaluate(
				{
					new Evaluate::Condition(new Evaluate::Const(1), new Evaluate::Const(-1),
					new Allow::Operator({ notEqual = new Allow::NotEqual(this), new Allow::Class<Game::Competitor>(true),
					// field of view
					new Allow::StatInRange(ifDistance = new Evaluate::Distance(this, viewOffset), nullptr, new Evaluate::Const(viewRange))
					}, Allow::Operator::And)),

					distance1 = new Evaluate::Distance(this, Vector2D(), Position, Evaluate::Distance::LenghtSq),
				},
				Evaluate::Operator::division
				);

				if (ifDistance != nullptr)
					ifDistance->toCheck = this;

				Game::getBest(world, aimsToAvoid, aimsToAvoid.size(), &evaluate, 0);

				if (ifDistance != nullptr)
					ifDistance->toCheck = nullptr;

			}

			
		}
	}

	bool Enemy::onDeath()
	{
		if (alive && player != nullptr)
		{
			alive = false;
			static float maxDistance = 600;
			if ((getPosC().position - player->getPosC().position).getLenghtSq() < maxDistance*maxDistance)
				player->score++;

			for each (auto it in world)
				if (it != nullptr && it != this && (getPosC().position - it->getPosC().position).getLenghtSq() < maxDistance*maxDistance)
					it->getHp().addForce(1.);

			deathTimer.restart();
		}
		efBodyWarrior->onDeath();
		return 
			Competitor::onDeath();

		return deathTimer.isReady();
	}
}


////////////
/*bool Enemy::stayWeaponInFront(const string& animCode, const string& keyCode, float *res, float desiredStep, float speed, float tolerance)
{

float actualStep = getAnimation(animCode).getStep();
float stepDifference = desiredStep - actualStep;


if (stepDifference * stepDifference > tolerance * tolerance)
{
(*res) -= stepDifference * speed;
press(keyCode);
return false;
}

return true;
}*/

// one-state ai
/**auto actionSet = new ActionSet(
{
// follow aim
new ActionLookAt( &aim, randRange(0,70), 0.25),
new ActionMoveTo(&aim, randRange(0, 100), Vector2D(randRange(-100, 100), randRange(50, 250)), Vector2D(1.1, 1.1), true, true),
new ActionMoveTo( positionOfMap , Vector2D(400, 900), Vector2D(2.5, 400.1)),

// random movement
new ActionRandomPress("up", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5,0.75), 2.25 ),
new ActionRandomPress("down", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25 ),
new ActionRandomPress("left", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25 ),
new ActionRandomPress("right", randRange(0.1, 0.25), randRange(0.25, 0.5), randRange(0.5, 0.75), 2.25 ),

// keys
new ActionRandomPress("s1", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
new ActionRandomPress("s2", randRange(0.05, 0.1), randRange(0.1, 0.3), randRange(0.5, 0.75), 1.25),
new ActionRandomPress("jump", randRange(0.05, 0.25), randRange(0.25, 0.6), randRange(0.125, 0.5), 1.05),

// mouse move
new ActionRandomDrag(&drag.x, randRange(-10, -3), randRange(3, 10)),
new ActionRandomDrag(&drag.y, randRange(-10, -3), randRange(3, 10))
});
efMind->initActions({ actionSet });
efMind->setActualProcessedAction(actionSet);/**/


