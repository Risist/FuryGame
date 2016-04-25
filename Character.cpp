#include "Character.h"
#include "BulletGhost.h"


Character::Character()
{
}

#include "GameWorld.h"

extern Game::World world;


void Character::onInit()
{
	Game::Object::onInit();

	model.deserialize("model_shiveil.txt");
	initAllModels();


	addCollider(CircleCollider(Vector2D(), 50.f));

	idAnimAtU = addResource(Resource<float>());
	getResource_f(idAnimAtU).resetVelocity = 0.75;
	getResource_f(idAnimAtU).inverseMass = 0.5;

	idAnimAtH = addResource(Resource<float>());
	getResource_f(idAnimAtH).resetVelocity = 0.75;
	getResource_f(idAnimAtH).inverseMass = 0.5;

	setInput("up", Control::Input(sf::Keyboard::W));
	setInput("down", Control::Input(sf::Keyboard::S));
	setInput("left", Control::Input(sf::Keyboard::A));
	setInput("right", Control::Input(sf::Keyboard::D));

	setInput("s1", Control::Input(sf::Mouse::Left));
	setInput("s2", Control::Input(sf::Mouse::Right));


	addAnimation("block", Animation("animBlockShield.txt"));
	addAnimation("atackH", Animation("swordAnim.txt"));
	addAnimation("atackU", Animation("swordAnimPush.txt"));

	// realms
	// position
	getPos().inverseMass = 0.9f;
	getPos().resetVelocity = 0.8f;

	// rotation
	getRot().inverseMass = 0.5;
	getRot().resetVelocity = 0.75f;
	gen.addParticle("particleTest.txt", 250, 1);
	//genSword.addParticle("swordParticle.txt", 50, 0.5);
}

void Character::movementScript(float movementSpeed)
{

	float power = getDrag().x;
	if (isPressed("s2"))
		 power *= 0.5;
	else if (isPressed("s1"))
		power *= 0.25;
	onSwing(power);

	if (isPressed("s1"))
	{
		if (isPressed("up"))
		{
			Vector2D v(0, -movementSpeed);
			v.rotate(getRotC().position);
			onPush(v);
		}else
			if (isPressed("down"))
		{
			Vector2D v(0, -movementSpeed * 0.125f);
			v.rotate(getRotC().position + 180);
			onPush(v);
		}
		return;
	}

	if (!(isPressed("up") && isPressed("down")))
	{
		if (isPressed("up"))
		{
			Vector2D v(0, -movementSpeed);
			v.rotate(getRotC().position);

			if (!(isPressed("left") && isPressed("right")))
			{
				if (isPressed("left"))
				{
					v.rotate(-45);
				}
				else if (isPressed("right"))
				{
					v.rotate(45);
				}
			}

			onPush(v);
		}
		if (isPressed("down"))
		{
			Vector2D v(0, movementSpeed);
			v.rotate(getRotC().position);

			if (!(isPressed("left") && isPressed("right")))
			{
				if (isPressed("left"))
				{
					v.rotate(45);
				}
				else if (isPressed("right"))
				{
					v.rotate(-45);
				}
			}

			onPush(v);
		}
	}
	if (!(isPressed("left") && isPressed("right")) && !isPressed("up") && !isPressed("down"))
	{
		if (isPressed("left"))
		{
			Vector2D v(-movementSpeed, 0);
			v.rotate(getRotC().position);
			onPush(v);
		}
		else if (isPressed("right"))
		{
			Vector2D v(movementSpeed, 0);
			v.rotate(getRotC().position);
			onPush(v);
		}
	}

	

}
void Character::shieldScript()
{
	switch (shieldState)
	{
	case Character::release:
		if (isPressed("s1"))
			shieldState = Character::under;
		break;
	case Character::under:
		if (isPressed("s1"))
		{
			auto state = getAnimation("block").updateInRange(allModels, getAnimation("block").getSpeed());
			if (!state)
			{
				shieldState = Character::awaiting;
			}

		}
		else
			shieldState = Character::returns;
		break;
	case Character::awaiting:
		if (isPressed("s1"))
		{
			//gen.addParticle("particleTest.txt", 1, 1);
		}
		else
			shieldState = Character::returns;
		break;
	case Character::returns:
		if (!isPressed("s1"))
		{
			auto state = getAnimation("block").updateInRange(allModels, -getAnimation("block").getSpeed());
			if (!state)
				shieldState = Character::release;

		}
		else
			shieldState = Character::under;
		break;
	}
}
void Character::swordScript()
{

	switch (swordState)
	{
	case Character::release:
		if (isPressed("s2"))
		{
			swordState = Character::under;
		}
		break;
	case Character::under:
		if (isPressed("s2"))
		{
			auto state = getAnimation("atackH").updateInRange(allModels, getAnimation("atackH").getSpeed());
			if (!state)
				swordState = Character::awaiting;

		}
		else
			swordState = Character::returns;
		break;
	case Character::awaiting:
		if (isPressed("s2"))
		{

		}
		else
		{
			swordState = Character::returns;
			onSwing(10);
		}
		break;
	case Character::returns:
		if (!isPressed("s2"))
		{
			auto state = getAnimation("atackH").updateInRange(allModels, -getAnimation("atackH").getSpeed() * 2.5);
			if (!state)
				swordState = Character::release;

		}
		else
			swordState = Character::under;
		break;
	default:
		break;
	}
	/*if (isPressed("s2"))
	{
		getAnimation("atackH").updateReturn(allModels);

		//getResource_f(idAnimAtU).addForce(-getDrag().y);
		//getResource_f(idAnimAtH).addForce(-getDrag().x);
	}*/

	//getAnimation("atackH").updateInRange(allModels, getResourceC_f(idAnimAtH).velocity);
	//getAnimation("atackU").updateInRange(allModels, getResourceC_f(idAnimAtU).velocity);
}

void Character::onUpdate(float dt)
{
	Game::Object::onUpdate(dt);
	gen.update(dt*2, model);
	genSword.update(dt * 2);

	resetInput();
	standardInputUpdate();
	standardMouseUpdate(0.04, Vector2D(7.5f, 7.5f));


	movementScript( 3* dt * (isPressed("s1") ? 2 : 1));
	shieldScript();
	swordScript();

	static Control::Timer timer(2.5);
	if (isPressed("s2") && timer.isReady())
	{
		world.push_back(new BulletGhost(this) );
	}
}
void Character::onDisplay(Camera& cam)
{
	gen.display(cam);
	genSword.display(cam, *allModels[4]);
	Competitor::onDisplay(cam);
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		for (size_t i = 0; i < colliders.size(); ++i)
			colliders[i].getColliderAccordingToSprite(model).display(cam, Color(255, 150, 150));


	cam.follow(model, -350);
}

void Character::onCollision(Game::Object* other, const pair<int, int >& firstColliderId)
{
	//Vector2D toOther = other->getPosC().position - getPosC().position;

	other->getPos().addForce( getPosC().velocity.normalised() * (isPressed("s1") ? 25 : 5 ));
}

