#pragma once
#include "GameObject.h"
#include "evaluate.h"
#include "allow.h"

namespace Game
{
	class World : public vector < Object* >
	{
	public:
		World();
		~World();

		void push_back(Object* s, bool dynamic = false)
		{
			if (s == nullptr)
				return;

			if (dynamic)
				toAdd.push_back(s);
			else
			{
				vector<Object*>::push_back(s);
				s->onInit();
			}
		}
		void preInit(Object* s)
		{

		}
		void push_backNoInit(Object* s, bool dynamic = false)
		{
			if (s == nullptr)
				return;

			if (dynamic)
				toAdd.push_back(s);
			else
			{
				vector<Object*>::push_back(s);
			}
		}

		void update(Camera& cam, float dt = 1);

		vector < Object* > toAdd;
	};


	// check every object from "world"
	//  and try to find object 
	// with greather evaluation from "evaluate" object
	Object* getBest(const vector<Object*>& world, Evaluate::Base* evaluate, float minimalEvaluation = 0 );


	// check every object from "world"
	//  and try to find object n objects
	// with greather evaluation from "evaluate" object
	// assume that whereToSave's size is big enough
	vector<Object*>& getBest(const vector<Object*>& world, vector<Object*>&whereToSave, size_t n, Evaluate::Base* evaluate, float minimalEvaluation = 0);

}

