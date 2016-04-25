#pragma once
#include "GameMultiEfect.h"
#include "utility.h"
#include "Model.h"
#include "Animation.h"
#include "CircleCollider.h"

namespace Game
{
	class Object : public MultiEfect
	{
	public:
		Object();

		

		// called when object is created
		// only once per object
		// should be used to load heavy data such like textures/models form disc
		void onInit() override;
		// similar to one above but in this case it could be called multiplay times per application run
		// every round, turn, respawn ect. it is used to restore the initial state without loading heavy data
		// also can send informations to global system about pervous existence
		virtual void onReset() override;


		// event called every frame when the object is alive
		// dt parametr ( abberviation of delta time ) tells how much time elapsed from last call the event
		// most important function, there should be putted all autonomous action of the object
		//----------------------------------------- GameObject
		// updates all resources
		void onUpdate(float dt) override;
		// called every screen refresh
		// there should be putted every drawing request
		//----------------------------------------- GameObject
		// displays and actualise data of the model
		void onDisplay(Camera& cam) override;


		// main function to deal with environment
		// each of resources ( such as position, rotation, health, energy ect ) should be numbered
		// it is described by resourceId parametr
		// parametr force tells the function with how big force you want to change value of the resource
		// the force can be possitive or negative 
		// last parametr called causer tells you who want to make an influence on you
		// the reaction on interaction can depend on causers parametrs
		// also it can be used to make an influence on causer as a revenge
		// type of causer can be cast to another which could tell you more informations about causer
		// if you use causers data make sure that it is not equal to nullptr
		// by nullptr there is marked situation when the object calls itself
		void onInteract(float force, size_t resourceId, Object* causer) override;
		// look on description of float version
		void onInteract(const Vector2D& force, size_t resourceId, Object* causer) override;


		// this event tells when the object is considered to be dead
		// default behaviour is that the object can't die
		// ------------------------- GameObject
		// alive state depends on health state
		// once it hits less health than 0 object is dead
		bool isAlive();

		/*** Resource ***/

		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of float type
		// changable version
		Resource<float>& getResource_f(size_t resourceId) override;

		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of Vector2D type
		// changable version
		Resource<Vector2D>& getResource_v2(size_t resourceId) override;

		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of float type
		// constant version
		const Resource<float>& getResourceC_f(size_t resourceId) const override;
		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of Vector2D type
		// constant version
		const Resource<Vector2D>& getResourceC_v2(size_t resourceId) const override;

		// add new type of resource which stores float data
		// returns id of newly added resource
		size_t addResource(const Resource<float>& s)
		{
			resource_f.push_back(s);
			return resource_f.size() - 1;
		}
		// add new type of resource which stores Vector2D data
		// returns id of newly added resource
		size_t addResource(const Resource<Vector2D>& s)
		{
			resource_v2.push_back(s);
			return resource_v2.size() - 1;
		}
		// add most common types of resource
		void addStandardResource();
		// remove all currently added types of resource
		void removeAllResource();

		// add new animation to list of available
		// you can interract with this animation by "code" key
		// code should be not so long, because the lenght can increase time needed to find the animation
		void addAnimation(const string& code, const Animation& newAnim)
		{
			animations[code] = newAnim;
		}
		// get previously added animation signed by "code" key
		// best idea is to save somewhere returned reference, because searching for code is not instant
		Animation& getAnimation(const string& code)
		{
			return animations[code];
		}

		/******New Collisions ******/

		bool isOnCollision(const vector<Object*>& world) const;
		bool isOnCollision(const CircleCollider& collider, size_t idMin = 0, int idMax = -1) const;
		bool isOnCollision(Object *object, size_t myIdMin = 0, int myIdMax = -1, size_t idMin = 0, int idMax = -1) const;

		void checkForCollision(const vector<Object*>& world) const ;
		void checkForCollision(Object* object, size_t myIdMin = 0, int myIdMax = -1, size_t idMin = 0, int idMax = -1) const;
		void checkForCollision(const ColliderInfo& collider, bool otherRunOnCollision = true, bool myRunOnCollision = true, size_t idMin = 0, int idMax = -1) const;

		// insert new collider into the container
		void addCollider(const ColliderInfo& s)
		{
			colliders.push_back(s);
		}

		// if is equal to false 
		// and when other object use checkForCollision 
		// and there is intersection
		// check for collision will call onCollision event for both objects
		bool isCheckingForCollision;
		vector<ColliderInfo> colliders;
		// if the other object is not colliding with this one 
		// then it is assumed that is not on collision with any else
		// if radius is negative then always check with any of colliders
		ColliderInfo layerCollider;

		
	
		vector<Model*> allModels;
		void initAllModels( Model& model);
		//protected:
		//private:
		vector<Resource<float> > resource_f;
		vector<Resource<Vector2D> > resource_v2;
		map<string, Animation> animations;

	private:
		using MultiEfect::setOwner;
		using MultiEfect::getOwner;
		using MultiEfect::hasOwner;
		using MultiEfect::colliderInfo;

	};

}