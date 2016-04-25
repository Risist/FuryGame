#include "GamePlayer.h"



extern RenderWindow wnd;

namespace Game
{
	void Player::standardInputUpdate()
	{
		for (auto it = inputs.begin(); it != inputs.end(); ++it)
			if (it->second.isReady())
				press(it->first);
	}
	void Player::standardMouseUpdate(float speed, const Vector2D& maxValue, const Vector2D& mouseMovementLock)
	{
		auto v = mouseInput.getDiffirence(wnd);
		mouseInput.lockedPoint = Control::MouseDrag::lockMouseOnWindow(wnd, mouseMovementLock);

		setDrag(Vector2D(clamp(v.x*speed, -maxValue.x, maxValue.x), clamp(v.y*speed, -maxValue.y, maxValue.y)));
	}

}

/*
Player::Player()
	: keyUp(sf::Keyboard::W)
	, keyDown(sf::Keyboard::S)
	, keyLeft(sf::Keyboard::A)
	, keyRight(sf::Keyboard::D)
	, keyAt1(sf::Mouse::Left)
{
}

void Player::moveAsPlayer(const Vector2D& force, float addictionalRotation)
{
	// add movement force
	//position.addForce(force);
	//rotation.addForce(minimalAngleDiffirence(rotation.position + addictionalRotation, Vector2D(force.x, -force.y).angle()) * 0.05);
	onPush(force, nullptr);
	onSwing(minimalAngleDiffirence(getRotC().position + addictionalRotation, Vector2D(force.x, -force.y).angle()) * 0.05, nullptr);

	//cout << " position " << getPosC().position << ", velocity " << getPosC().velocity << ", force " << getPosC().force << ", ";
	//cout << " inverseMass " << getPosC().inverseMass << ", resetForce " << getPosC().resetForce << ", reset Velocity " << getPosC().resetVelocity << "\n";
}

void Player::onInit()
{
	GameObject::onInit();
	idAt1 = addResource(Resource<float>());
	getResAt1().inverseMass = 0.020;
	getResAt1().resetVelocity = 0.8;

	idAt2 = addResource(Resource<float>());
	getResAt2().inverseMass = 0.05;
	getResAt2().resetVelocity = 0.8;

	model.deserialize("modelHero1.txt");
	axe.deserialize("modelAxe.txt");
	axe.initAllModels(allModelsAxe);

	addAnimation("axe1", Animation("animAxe1.txt"));
	addAnimation("axe2", Animation("animAxe2.txt"));

	// realms
	// position
	getPos().inverseMass = 0.9f;
	getPos().resetVelocity = 0.8f;

	// rotation
	getRot().inverseMass = 0.5;
	getRot().resetVelocity = 0.75f;

	movementSpeed = 5.f;
	atack1Speed = 1.f;
	atack2Speed = 1.f;

}
void Player::movementScript()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			moveAsPlayer(Vector2D(0, -movementSpeed).getRotated(-45), -90);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveAsPlayer(Vector2D(0, -movementSpeed).getRotated(45), 90);
		else
			moveAsPlayer(Vector2D(0, -movementSpeed));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			moveAsPlayer(Vector2D(0, movementSpeed).getRotated(45), 90);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveAsPlayer(Vector2D(0, movementSpeed).getRotated(-45), -90);
		else
			moveAsPlayer(Vector2D(0, movementSpeed));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveAsPlayer(Vector2D(-movementSpeed, 0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveAsPlayer(Vector2D(movementSpeed, 0));
}
void Player::movementScript_version2()
{
	if (keyUp.isReady() )
	{
		Vector2D v(0,-movementSpeed);
		v.rotate(getRotC().position);
		
		if (keyLeft.isReady())
		{
			v.rotate(-45);
		}
		else if (keyRight.isReady())
		{
			v.rotate(45);
		}

		onPush(v, nullptr);
	}
	else if (keyDown.isReady())
	{
		Vector2D v(0, movementSpeed);
		v.rotate(getRotC().position);

		if (keyLeft.isReady())
		{
			v.rotate(45);
		}
		else if (keyRight.isReady())
		{
			v.rotate(-45);
		}

		onPush(v, nullptr);
	}
	else if (keyLeft.isReady())
	{
		Vector2D v( -movementSpeed, 0);
		v.rotate(getRotC().position);
		onPush(v, nullptr);
	}
	else if (keyRight.isReady())
	{
		Vector2D v(movementSpeed, 0);
		v.rotate(getRotC().position);
		onPush(v, nullptr);
	}

	drag(mouseInput.getDiffirence(wnd) * 0.1f);
	mouseInput.lockedPoint = Control::MouseDrag::lockMouseOnWindow(wnd, Vector2D(100, 100));


	getAnimation("axe1").updateInRange(allModelsAxe, getResAt1().velocity );
	getAnimation("axe2").updateInRange(allModelsAxe, getResAt2().velocity );
}

void Player::drag(const Vector2D& force)
{
	Vector2D _force = Vector2D(
		clamp(force.x, -5.f, 5.f),
		clamp(force.y, -10.f, 10.f)
		);

	float characterRotationSpeed = 1.f;
	if (keyAt1.isReady())
	{
		getResAt1().addForce(clamp(force.x, -17.5f, 17.5f));
		getResAt2().addForce(_force.y);
		characterRotationSpeed *= 0.5;
	}
	else
	{
		//getResAt1().addForce(_force.x*0.05);
		//getResAt1().addForce(-animAxe1.steap * 0.1f);
		//getResAt2().addForce(-animAxe2.steap * 0.1f);
	}

	getRot().addForce(_force.x * characterRotationSpeed);
}

void Player::atack1Script()
{
	static bool pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		pressed = true;
		getAnimation("axe1").updateInRange(allModelsAxe, atack1Speed);
	}
	else
	{
		if (pressed == true)
		{
			atack1Speed *= -1;
			pressed = false;
		}
	}

}
void Player::atack2Script()
{
	static bool pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		pressed = true;
		getAnimation("axe2").updateInRange(allModelsAxe, atack2Speed);
	}
	else
	{
		if (pressed == true)
		{
			atack2Speed *= -1;
			pressed = false;
		}
	}
}

void Player::onUpdate(float dt)
{
	movementScript_version2();
	//atack1Script();
	//atack2Script();

	GameObject::onUpdate(dt);
}
void Player::onDisplay(Camera& cam)
{
	axe.draw(cam, model);
	GameObject::onDisplay(cam);
	cam.follow(model, - 450);
}
/**/