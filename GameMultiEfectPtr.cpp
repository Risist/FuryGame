#include "GameMultiEfectPtr.h"


namespace Game
{
	MultiEfectPtr::MultiEfectPtr(initializer_list<Efect*> efects, Object* owner) : Efect(owner)
	{
		for each (auto it in efects)
			el.push_back(it);
	}

	void MultiEfectPtr::onInit()
	{
		for (int i = 0; i < el.size(); ++i)
			if ( el[i]->activated )
		{
			el[i]->setOwner(getOwner());
			el[i]->onInit();
		}
		onReset();
	}
	void MultiEfectPtr::onReset()
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onReset();
	}

	/*** life cycle ***/
	bool MultiEfectPtr::isAlive()
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				return true;
		return false;
	}
	bool MultiEfectPtr::onDeath()
	{
		bool b = false;
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				b = b || el[i]->onDeath();
		return b;
	}

	void MultiEfectPtr::onUpdate(float dt)
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onUpdate(dt);
	}
	void MultiEfectPtr::onDisplay(Camera& cam)
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onDisplay(cam);
	}

	/*** influence of environment ***/
	void MultiEfectPtr::onInteract(float force, size_t resourceId, Object* causer)
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onInteract(force, resourceId, causer);
	}
	void MultiEfectPtr::onInteract(const Vector2D& force, size_t resourceId, Object* causer)
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onInteract(force, resourceId, causer);
	}


	/*** collisions	***/
	void MultiEfectPtr::onCollision(const ColliderInfo& otherCollider)
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i]->activated)
				el[i]->onCollision(otherCollider);
	}

	void MultiEfectPtr::setColliderInfo(ColliderInfo *s)
	{
		for (int i = 0; i < el.size(); ++i)
			el[i]->setColliderInfo(s);
	}
}