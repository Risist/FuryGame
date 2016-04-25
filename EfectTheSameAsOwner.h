#pragma once
#include "GameObject.h"

class EfectTheSameAsOwner : public Game::Efect
{
public:
	EfectTheSameAsOwner(){}

	bool isAlive()
	{ 
		return getOwner()->isAlive(); 
	}
	bool onDeath() override 
	{ 
		return getOwner()->onDeath();
	}

	/*** influence of environment ***/

	void onInteract(float force, size_t resourceId, Game::Object* causer = nullptr) override
	{
		getOwner()->onInteract(force, resourceId, causer);
	}
	void onInteract(const Vector2D& force, size_t resourceId, Game::Object* causer = nullptr) override
	{
		getOwner()->onInteract(force, resourceId, causer);
	}

	/**** resource changable ***/
	Resource<float>& getResource_f(size_t resourceId) override 
	{ 
		return getOwner()->getResource_f(resourceId); 
	}
	Resource<Vector2D>& getResource_v2(size_t resourceId) override
	{
		return getOwner()->getResource_v2(resourceId);
	}

	const Resource<float>& getResourceC_f(size_t resourceId) const override
	{
		return getOwner()->getResourceC_f(resourceId);
	}
	const Resource<Vector2D>& getResourceC_v2(size_t resourceId) const override
	{
		return getOwner()->getResourceC_v2(resourceId);
	}

	void onCollision(const ColliderInfo& otherCollider) override
	{
		getOwner()->onCollision( otherCollider);
	}
};

