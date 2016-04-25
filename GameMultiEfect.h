#pragma once
#include "GameMultiEfectPtr.h"

namespace Game
{

	class MultiEfect : public MultiEfectPtr
	{
	public:
		MultiEfect(initializer_list<Efect*> efects = {}, Object* owner = nullptr);
		~MultiEfect();

		// add new efect to container
		// if newEfect is empty does nothing
		Efect* addEfect(Efect* newEfect, bool active = true)
		{
			if (newEfect == nullptr)
				return nullptr;

			MultiEfectPtr::addEfect(newEfect, active);
			initEfect(newEfect);
			return newEfect;
		}
		Efect* addEfectNoInit(Efect* newEfect, bool active = true)
		{
			if (newEfect == nullptr)
				return nullptr;

			MultiEfectPtr::addEfect(newEfect, active);
			return newEfect;
		}
		Efect* initEfect(Efect* newEfect)
		{
			newEfect->setOwner(getOwner());
			newEfect->onInit();
			return newEfect;
		}

	private:
		vector<Efect*> el;
	};


}