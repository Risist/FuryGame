#pragma once
#include "Camera.h"

#include "utility.h"
#include "Resource.h"
#include "ColliderInfo.h"
using namespace std;

namespace Game
{
	class Object;
	class Efect;

	// simple interface which standardizes events which could be called by environment
	// that real objects only need to fill them ( not all but at least a part to make a meaningful and expected behaviour)
	// supports as were mentioned earier events to deal with environment ( influence on a dimension )
	// but as well there are events to deal with game sustems flow such as death/ alive state
	class Event
	{
	public:
		virtual ~Event(){}

		/*** creation ***/
		// called when object is created
		// only once per object
		// should be used to load heavy data such like textures/models form disc
		virtual void onInit();
		// similar to one above but in this case it could be called multiplay times per application run
		// every round, turn, respawn ect. it is used to restore the initial state without loading heavy data
		// also can send informations to global system about pervous existence
		virtual void onReset();

		/*** life cycle ***/
		// this event tells when the object is considered to be dead
		// default behaviour is that the object can't die
		virtual bool isAlive(){ return true; }
		// when the object is considered to be dead there is executed a differend behaviour
		// firstly it can be used to display message to the player
		// for example a menu with button called "respawn" which uses onReset event
		// secound idea is that the object could want to finish the started actions or just simply run death animation
		// after death animation you can pick up drop or something like that
		// some words about return value
		// if returns true that simply mean that the object can be removed and destroyed from the game (permanently)
		// by default returns true
		virtual bool onDeath(){ return true; }

		/*** main finctions ***/
		// event called every frame when the object is alive
		// dt parametr ( abberviation of delta time ) tells how much time elapsed from last call the event
		// most important function, there should be putted all autonomous action of the object
		virtual void onUpdate(float dt){}
		// called every screen refresh
		// there should be putted every drawing request
		virtual void onDisplay(Camera& cam){}

		/*** influence of environment ***/


		// list of most typical dimension types
		// created only for easier usage, does not require to use it in a real game system
		enum Dimensions_f
		{
			hp, // health state
			rot, // rotation state
			vis, // visiblity cannal
			dimensions_fCount // how many dimensions are considered in typical usage
		};
		enum Dimensions_v2
		{
			pos,
			dimensions_v2Count
		};

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
		virtual void onInteract(float force, size_t resourceId, Object* causer = nullptr){};
		// look on description of float version
		virtual void onInteract(const Vector2D& force, size_t resourceId, Object* causer = nullptr){};


		// few function to help with using onInteract event

		// make an influence on this object by changing its position
		// for more informations look on onInteract function
		void onPush(const Vector2D& force, Object* causer = nullptr){ onInteract(force, pos, causer); }
		// make an influence on this object by changing its health state
		// for more informations look on onInteract function
		void onDamage(float force, Object* causer = nullptr){ onInteract(force, hp, causer); }
		// make an influence on this object by changing its rotation
		// for more informations look on onInteract function
		void onSwing(float force, Object* causer = nullptr){ onInteract(force, rot, causer); }

		/**** resource changable ***/

		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of float type
		// changable version
		virtual Resource<float>& getResource_f(size_t resourceId) { return Resource < float >(); }

		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of Vector2D type
		// changable version
		virtual Resource<Vector2D>& getResource_v2(size_t resourceId) { return Resource < Vector2D >(); }

		// get the informations connected with localisation of the object
		// changable version
		Resource<Vector2D>& getPos(){ return getResource_v2(pos); }
		// get the informations connected with rotation of the object
		// changable version
		Resource<float>& getRot(){ return getResource_f(rot); }
		// get the informations connected with health state of the object
		// changable version
		Resource<float>& getHp(){ return getResource_f(hp); }
		// get the informations connected with visiblity level of the object
		// changable version
		Resource<float>& getVis(){ return getResource_f(vis); }



		/**** resource constant ***/
		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of float type
		// constant version
		virtual const Resource<float>& getResourceC_f(size_t resourceId) const { return Resource < float >(); }
		// function used to getting basic informations about the object
		// returns data of resourceId dimmension
		// this one returns only resource of Vector2D type
		// constant version
		virtual const Resource<Vector2D>& getResourceC_v2(size_t resourceId) const { return Resource < Vector2D >(); }

		// get the informations connected with localisation of the object
		// constant version
		const Resource<Vector2D>& getPosC() const { return getResourceC_v2(pos); }
		// get the informations connected with rotation of the object
		// constant version
		const Resource<float>& getRotC() const { return getResourceC_f(rot); }
		// get the informations connected with health state of the object
		// constant version
		const Resource<float>& getHpC() const { return getResourceC_f(hp); }
		// get the informations connected with visiblity level of the object
		// constant version
		const Resource<float>& getVisC() const { return getResourceC_f(vis); }

		/*** collisions	***
		// event used to check wether there is collision between this and the oter object
		// returned value has two parts - first of them describes id of first collider from this object and secound from the other
		// if there is on collision at all returns constant vlaue - noCollision which at least has one of parts as negative value
		// by default collision is impossible
		static const pair<int, int> noCollision;
		virtual int isOnCollision(const CircleCollider& other) const{ return noCollision.first; }
		virtual pair<int, int> isOnCollision(const Object* other) const{ return noCollision; }

		// this event is called if a collision between this and the other object were detected
		// other parametr is a piontner to the object with the collision were detected
		// parametr firstColliderId describes id of first coliders from this and the other object that were on collision 
		virtual void onCollision(Object* other, const pair<int, int >& firstColliderId){};
		/**/

		// this event is called if a collision between this and the other object were detected
		// other shuld be treated as real object, not as component
		// if you want to affect on other object just try to do it with other event
		// myCollider and otherCollider are colliders after update of position
		//virtual void onCollision(Efect*other, const ColliderInfo& otherCollider, const ColliderInfo& myCollider){}
		virtual void onCollision(const ColliderInfo& otherCollider){}


	};

}