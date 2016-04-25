#include "GameObject.h"

namespace Game
{

	Object::Object() : MultiEfect({}, this), isCheckingForCollision(false), layerCollider(CircleCollider(Vector2D(), -1))
	{
	}

	void Object::initAllModels( Model& model)
	{
		model.initAllModels(allModels);
	}

	// called when object is created
	// only once per object
	// should be used to load heavy data such like textures/models form disc
	void Object::onInit()
	{
		//removeAllResource();
		//addStandardResource();
		MultiEfect::onInit();
		onReset();
	}
	// similar to one above but in this case it could be called multiplay times per application run
	// every round, turn, respawn ect. it is used to restore the initial state without loading heavy data
	// also can send informations to global system about pervous existence
	void Object::onReset()
	{
		removeAllResource();
		addStandardResource();
		MultiEfect::onReset();
	}

	bool Object::isAlive()
	{
		return getHpC().position > 0;
	}


	void Object::removeAllResource()
	{
		resource_f.clear();
		resource_v2.clear();
	}
	void Object::addStandardResource()
	{

		//hp
		addResource(Resource<float>(100));
		getHp().resetVelocity = 0.75;
		//rot
		addResource(Resource<float>());
		getRot().resetVelocity = 0.75;
		// vis
		addResource(Resource<float>());
		getVis().resetVelocity = 0.75;

		// pos
		addResource(Resource<Vector2D>());
		getPos().resetVelocity = 0.75;

	}

	// event called every frame when the object is alive
	// dt parametr ( abberviation of delta time ) tells how much time elapsed from last call the event
	// most important function, there should be putted all autonomous action of the object
	void Object::onUpdate(float dt)
	{
		for (size_t i = 0; i < resource_f.size(); ++i)
			resource_f[i].update(dt);

		for (size_t i = 0; i < resource_v2.size(); ++i)
			resource_v2[i].update(dt);

		MultiEfect::onUpdate(dt);
	}
	// called every screen refresh
	// there should be putted every drawing request
	void Object::onDisplay(Camera& cam)
	{
		MultiEfect::onDisplay(cam);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && layerCollider.collider.range > 0)
			layerCollider.getActualCollider().display(cam, Color(100, 200, 100, 75));
	}

	// main function to deal with environment
	// each of resources ( such as position, rotation, health, energy ect ) should be numbered
	// it is described by resourceId parametr
	// parametr force tells the function with how big force you want to change value of the resource
	// the force can be possitive or negative 
	// last parametr called causer tells you who want to make an influence on you
	// the reaction on interaction can depend on causers parametrs
	// also it can be used to make an influence on causer as a revenge
	// type of causer can be cast to another which could tell you more informations about causer
	void Object::onInteract(float force, size_t resourceId, Object* causer)
	{
		resource_f[resourceId].addForce(force);

		MultiEfect::onInteract(force, resourceId, causer);
	}
	// look on description of float version
	void Object::onInteract(const Vector2D& force, size_t resourceId, Object* causer)
	{
		resource_v2[resourceId].addForce(force);

		MultiEfect::onInteract(force, resourceId, causer);
	}

	/*** Resource ***/
	// function used to getting basic informations about the object
	// returns data of resourceId dimmension
	// this one returns only resource of float type
	// changable version
	Resource<float>& Object::getResource_f(size_t resourceId)
	{
		return resource_f[resourceId];
	}

	// function used to getting basic informations about the object
	// returns data of resourceId dimmension
	// this one returns only resource of Vector2D type
	// changable version
	Resource<Vector2D>& Object::getResource_v2(size_t resourceId)
	{
		return resource_v2[resourceId];
	}

	// function used to getting basic informations about the object
	// returns data of resourceId dimmension
	// this one returns only resource of float type
	// constant version
	const Resource<float>& Object::getResourceC_f(size_t resourceId) const
	{
		return resource_f[resourceId];
	}
	// function used to getting basic informations about the object
	// returns data of resourceId dimmension
	// this one returns only resource of Vector2D type
	// constant version
	const Resource<Vector2D>& Object::getResourceC_v2(size_t resourceId) const
	{
		return resource_v2[resourceId];
	}

	bool Object::isOnCollision(const vector<Object*>& world) const
	{
		for each(auto it in world)
			if (it != nullptr && isOnCollision(it))
				return true;
		return false;
	}
	bool Object::isOnCollision(Object *object, size_t myIdMin, int myIdMax, size_t idMin, int idMax) const
	{
		if (object == nullptr || object == this || object->isAlive() == false ||
			(
			layerCollider.collider.range < 0 || object->layerCollider.collider.range < 0 ||
			layerCollider.getActualCollider().isOnCollision(object->layerCollider.getActualCollider())
			) == false
			)
			return false;

		if (idMax < 0)
			idMax = object->colliders.size() - 1;

		if (myIdMax < 0)
			myIdMax = colliders.size() - 1;

		for each(auto it in colliders)
			//for (auto it = colliders.begin() + myIdMin; it != colliders.begin() + myIdMax; it++)
			if (object->isOnCollision(it.getActualCollider(), idMin, idMax))
				return true;
		return false;
	}
	bool Object::isOnCollision(const CircleCollider& collider, size_t idMin, int idMax) const
	{
		if (idMax < 0) 
			idMax = colliders.size() - 1;

		for each(auto it in colliders)
		//for (auto it = colliders.begin() + idMin; it != colliders.begin() + idMax; it++)
			if (collider.isOnCollision(it.getActualCollider()))
				return true;
		return false;
	}
	
	

	void Object::checkForCollision(const vector<Object*>& world) const
	{
		for each (auto it in world)
			checkForCollision(it);
	}
	void Object::checkForCollision(Object* object, size_t myIdMin, int myIdMax, size_t idMin, int idMax) const
	{
		if (object == nullptr || object == this || object->isAlive() == false)
			return;
		/*if (layerCollider.collider.range > 0 && object->layerCollider.collider.range > 0 &&
			layerCollider.getActualCollider().isOnCollision(object->layerCollider.getActualCollider()))
			return;*/


		if (myIdMax < 0)
			myIdMax = colliders.size();

		//for each(auto it in colliders)
			//object->checkForCollision(it, !object->isCheckingForCollision, true, idMin, idMax);

		auto itLast = colliders.begin() + myIdMax;
		for (auto it = colliders.begin() + myIdMin; it != itLast; it++)
			object->checkForCollision(*it, !object->isCheckingForCollision, true, idMin, idMax);
	}
	void Object::checkForCollision(const ColliderInfo& collider, bool otherRunOnCollision, bool myRunOnCollision, size_t idMin, int idMax) const
	{
		if (idMax < 0)
			idMax = colliders.size();


		//for each(auto it in colliders)
			//it.checkForColliion(collider, otherRunOnCollision, myRunOnCollision);

		auto itLast = colliders.begin() + idMax;
		for (auto it = colliders.begin() + idMin; it != itLast; ++it)
			it->checkForColliion(collider, otherRunOnCollision, myRunOnCollision);
	}
}