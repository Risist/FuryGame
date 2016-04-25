#include "GameObjectTemplate.h"

extern Game::World world;

//settings
#define className GameObjectTemplate
#define baseClassName Game::Object

className::className()
	: baseClassName()
{
}

// initialization
void className::onInit()
{
	baseClassName::onInit();

	//////////////// Most typical efect
	//////////////// uncomment if need
	//// graphics
	//addEfect(efModel = new EfectModel("model_.txt", nullptr, true, true) );
	//addEfect(efParticle = new EfectParticle( "particle_.txt", 1, 1, 1, 0, &efModel->model, nullptr) );
	//addEfect(efFollowCam = new EfectFollowCam( &efModel->model, -350) );
	//addEfect(efAnimation = new EfectAnimation("", "animation_.txt") );

	//// collision
	//addEfect(efCollidionResponse = new EfectCollisionResponse(5.5, 0.001, Vector2D() ) );
	//addEfect(efDamageOnCollision = new EfectDamageOnCollision(-0,-0) );
	//addEfect(efCheckForCollision = new EfectCheckForCollision(&world) );


	//// movement
	//addEfect(efTppMovement = new EfectTppMovement(4, 0.5) );
	//addEfect(efFollowAim = new EfectFollowAim(nullptr,0,0,1.f,Vector2D(),Vector2D(),false, false));

	//// debug
	//addEfect(efDebugCollider = new EfectDebugCollider(&efModel->model, sf::Keyboard::Z, Color(200, 200, 200, 100)));
	//addEfect(efDebugStat = new EfectDebugStat(Game::Event::hp, true, "object hp", Control::Input(sf::Keyboard::K)));

	//////////////// Collider
	//addCollider(CircleCollider(Vector2D(), 100.f));
	//////////////// Animation
	//addAnimation("", Animation("animation_.txt"));

	//////////////// Realms
	//// position
	getPos().position = Vector2D();
	getPos().velocity = Vector2D();
	getPos().force = Vector2D();
	getPos().inverseMass = 1;
	getPos().resetVelocity = 0.75;
	getPos().resetForce = 0;

	//// rotation
	getRot().position = 0;
	getRot().velocity = 0;
	getRot().force = 0;
	getRot().inverseMass = 1;
	getRot().resetVelocity = 0.75;
	getRot().resetForce = 0;

	//// hp
	getHp().position = 100;
	getHp().velocity = 0;
	getHp().force = 0;
	getHp().inverseMass = 1;
	getHp().resetVelocity = 0;
	getHp().resetForce = 0;

	//// vis
	getVis().position = 0;
	getVis().velocity = 0;
	getVis().force = 0;
	getVis().inverseMass = 1;
	getVis().resetVelocity = 0.75;
	getVis().resetForce = 0;
}
void className::onReset()
{
	baseClassName::onReset();
}

// live and death
bool className::isAlive()
{
	return baseClassName::isAlive();
}
bool className::onDeath()
{
	return baseClassName::onDeath();
}

// every frame update
void className::onUpdate(float dt)
{
	baseClassName::onUpdate(dt);
}
void className::onDisplay(Camera& cam)
{
	baseClassName::onDisplay(cam);
}

// interact
void className::onInteract(float force, size_t resourceId, Game::Object* causer)
{
	baseClassName::onInteract(force, resourceId, causer);
}
void className::onInteract(const Vector2D& force, size_t resourceId, Game::Object* causer)
{
	baseClassName::onInteract(force, resourceId, causer);
}

// collision

void className::onCollision(const ColliderInfo& otherCollider)
{
	baseClassName::onCollision(otherCollider);
}




#undef className
#undef baseClassName