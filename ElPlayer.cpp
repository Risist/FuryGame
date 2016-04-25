#include "ElPlayer.h"

#include "EfectJumpMovement.h"

#include "EfectWeaponAxe1h.h"
#include "EfectWeapon2hSword.h"
#include "EfectWeaponSword1h.h"
#include "EfectWeaponShield.h"

extern Game::World world;

namespace El
{
	Player::Player()
		: efWeaponLeft(nullptr), efWeaponRight(nullptr), score(0)
	{
	}


	void Player::onInit()
	{
		Game::Player::onInit();

		addEfect(new EfectCircleSign(
			60, Color(0, 150, 0), Color(0, 0, 0),
			nullptr, 100,
			new Evaluate::Stat_f(Game::Event::pos, Evaluate::Stat_f::position)
			));

		addEfect(efBodyWarrior = new EfectBodyWarrior(rand()%5) );

		addEfect(new EfectFollowCam(&efBodyWarrior->efHead->model, 180, 275));

	
		

		addEfect(new EfectDebugCollider(sf::Keyboard::Z, Color(200, 200, 200, 100)));
		

		getRot().resetVelocity = 0.65;
		getPos().resetVelocity = 0.65;

	
		// input
		setInput("up", Control::Input(Keyboard::W));
		setInput("down", Control::Input(Keyboard::S));
		setInput("left", Control::Input(Keyboard::A));
		setInput("right", Control::Input(Keyboard::D));
		setInput("s1", Control::Input(Mouse::Left));
		setInput("s2", Control::Input(Mouse::Right));
		setInput("jump", Control::Input(Keyboard::LShift, Control::Input::keyboard, Control::Input::pressed));

	}

	void Player::onDisplay(Camera& cam)
	{
		Game::Player::onDisplay(cam);
		
	}

	void Player::onUpdate(float dt)
	{
		
		Game::Player::onUpdate(dt);


		resetInput();
		standardInputUpdate();
		
		//standardMouseUpdate(0.25, Vector2D(75.f, 75.f));
		standardMouseUpdate(0.04, Vector2D(75.f, 75.f));

		Vector2D drag = getDrag();
		//drag.truncate(5.);
		drag.truncate(7.5);
		setDrag(drag);
	}

	bool Player::onDeath()
	{
		Game::Player::onDeath();
		efBodyWarrior->onDeath();
		return false;
	}
}
