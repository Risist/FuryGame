#pragma once
#include "GameEvent.h"

class ColliderInfo;

namespace Game
{

	class Object;

	class Efect : public Event
	{
	public:
		Efect(Object* owner = nullptr);


		// this function tells wheter this efect should be removed from container
		// so it coresponds to the efect, not to the owner
		bool isAlive() override { return true; }

		// set new owner of this efect
		void setOwner(Object* object)
		{
			owner = object;
		}

		// get actual owner of the efect
		// be aware
		Object* getOwner() const
		{
			return owner;
		}

		// returns true if owner were set
		bool hasOwner()
		{
			return owner != nullptr;
		}

		bool activated;
		virtual void setColliderInfo(ColliderInfo* s)
		{
			colliderInfo = s;
		}
		ColliderInfo *colliderInfo;
	private:
		Object* owner;
	};

}
