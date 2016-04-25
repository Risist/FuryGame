#pragma once
#include "GameWorld.h"
#include "efects.h"

// settings
#define className GameObjectTemplate
#define baseClassName Game::Object

class className : public baseClassName
{
public:
	className();

	//////////////// events
	//// initialization
	void onInit() override;
	void onReset() override;

	//// live and death
	bool isAlive() override;
	bool onDeath() override;

	//// every frame update
	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	//// interact
	void onInteract(float force, size_t resourceId, Game::Object* causer = nullptr) override;
	void onInteract(const Vector2D& force, size_t resourceId, Game::Object* causer = nullptr) override;

	//// collision
	void onCollision(const ColliderInfo& otherCollider) override;

	//////////////// Most typical efect
	//////////////// uncomment if need
	//// graphics
	//EfectModel *efModel;
	//EfectParticle *efParticle;
	//EfectFollowCam *efFollowCam;
	//EfectAnimation *efAnimation;

	//// collision
	//EfectCollisionResponse *efCollidionResponse;
	//EfectDamageOnCollision *efDamageOnCollision;
	//EfectCheckForCollision *efCheckForCollision;


	//// movement
	//EfectTppMovement *efTppMovement;
	//EfectFollowAim *efFollowAim;

	//// debug
	//EfectDebugCollider *efDebugCollider;
	//EfectDebugStat *efDebugStat;

};


#undef className
#undef baseClassName
