#pragma once
#include "GameObject.h"

namespace Game
{

	// addictional layer of abstraction of GameObject
	// which provide utility to remember state of decisions made by this object
	// by decisions is meant imitation of input pressing similar to a players input
	class Competitor : public Object
	{
	public:
		Competitor();

		bool onDeath() override
		{
			Object::onDeath();
			return false;
		}


		// simulate pressing the key signed by keyName
		void press(const string& keyName, float value = 1)
		{
			keys[keyName] += value;
		}
		// reset pressing single key signed by keyName
		void unpress(const string& keyName)
		{
			keys[keyName] = 0;
		}
		// checks whether the key signed by keyName is actually pressed
		bool isPressed(const string& keyName)
		{
			return keys[keyName] >= 1;
		}

		// reset(unpress) all available keys
		void resetInput();

		const Vector2D& getDrag() const
		{
			return drag;
		}
		void setDrag(const Vector2D& s)
		{
			drag = s;
		}

		// ai functions

		// uses drag.x to change rotation of the competitor
		// force scales from zero to maxForce 
		// dependingly on diffirence of competitors rotation and vector from the object to taken position
		// if the diffirence is lower than tolerance dont do anything
		bool lookAt(const Vector2D& position, float forceRatio = 1, float maxForce = 7.5, float tolerance = 50);

		// similar version to above but this case position is calculatet automaticaly
		// addictionaly to aims position is added its velocity multiplayed by dt
		// so it is simple prediction of where could be the object after dt cycles of main loop ( most probably 60/s)
		bool lookAt(Game::Object* aim, float dt = 0, float forceRatio = 1, float maxForce = 7.5, float tolerance = 10)
		{
			if (aim == nullptr)
				return false;

			return lookAt(aim->getPosC().position + aim->getPosC().velocity * dt, forceRatio, maxForce, tolerance);
		}

		// moves competitor to the point without rotation of body uses only pressing of up, down, left and right key
		// radius.x - minimal radius, radius.y - maximal radius
		// if the character is in range (radius.x, radius.y) returns true and does nothing
		// otherwise moves character into above spot
		// if diffirence in one axes is less than tolerance the character not will in this way
		bool moveTo(const Vector2D& position, const Vector2D& radius = Vector2D(0,100), const Vector2D& tolerance = Vector2D(50,50) );

		// similar version to above but this case position is calculatet automaticaly
		// addictionaly to aims position is added its velocity multiplayed by dt
		// so it is simple prediction of where could be the object after dt cycles of main loop ( most probably 60/s)
		bool moveTo(Game::Object* aim, float dt = 0, const Vector2D& radius = Vector2D(0, 100), const Vector2D& tolerance = Vector2D(50, 50))
		{
			if (aim == nullptr)
				return false;

			return moveTo(aim->getPosC().position + aim->getPosC().velocity * dt, radius, tolerance);
		}

	
		// if value of key is greather than 1 then key is pressed
		map<string, float> keys;
	protected:
		Vector2D drag;
	};

}