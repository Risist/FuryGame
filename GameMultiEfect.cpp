#include "GameMultiEfect.h"

namespace Game
{

	MultiEfect::MultiEfect(initializer_list<Efect*> efects, Object* owner) : MultiEfectPtr(efects, owner)
	{
	}

	MultiEfect::~MultiEfect()
	{
		for each(auto &it in el)
			delete it;
	}
}