#pragma once
#include "GameEfect.h"

namespace Game
{

	class MultiEfectPtr : public Efect
	{
	public:
		MultiEfectPtr(initializer_list<Efect*> efects = {}, Object* owner = nullptr);



		void onInit() override;
		void onReset() override;

		/*** life cycle ***/
		bool isAlive() override;
		bool onDeath() override;

		void onUpdate(float dt) override;
		void onDisplay(Camera& cam) override;

		/*** influence of environment ***/
		void onInteract(float force, size_t resourceId, Object* causer) override;
		void onInteract(const Vector2D& force, size_t resourceId, Object* causer) override;

		/*** collisions	***/
		void onCollision(const ColliderInfo& otherCollider) override;

		// add new efect to container
		// if newEfect is empty does nothing
		void addEfect(Efect* newEfect, bool active = true)
		{
			if (newEfect == nullptr)
				return;

			el.push_back(newEfect);
			newEfect->activated = active;
		}

		void setColliderInfo(ColliderInfo *s) override;

	private:
		vector<Efect*> el;
	};

}