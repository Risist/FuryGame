#pragma once
#include "EvaluateBase.h"



namespace Evaluate
{

	class Distance : public Base
	{
	public:


		enum Mode
		{
			PositionX,
			PositionY,
			Lenght,
			LenghtSq
		}mode;

		float getFromMode(const Vector2D& v, Mode mode) const
		{
			switch (mode)
			{
			case Evaluate::Distance::PositionX:
				return v.x;
			case Evaluate::Distance::PositionY:
				return v.y;
			case Evaluate::Distance::Lenght:
				return v.getLenght();
			case Evaluate::Distance::LenghtSq:
				return v.getLenghtSq();
			}
		}

		Distance(const Vector2D& _point, Param_t _param = Position, Mode _mode = Lenght, size_t _statId = Game::Object::pos)
			: toCheck(nullptr), point(point), param(_param), mode(_mode), statId(_statId)
		{
		}
		Distance(const Game::Object* _toCheck, const Vector2D& _point = Vector2D(), Param_t _param = Position, Mode _mode = Lenght, size_t _statId = Game::Object::pos)
			: toCheck(_toCheck), param(_param), mode(_mode), statId(_statId), point(_point)
		{
		}
		
		// if toCheck is equal to nullptr take constant point as an anchor
		// otherwise take param of toCheck object
		Vector2D point;
		const Game::Object* toCheck;

		size_t statId;
		Param_t param;

		const Vector2D& getAnchor() const
		{
			if (toCheck == nullptr)
				return point;
			else
			{
				Vector2D pos = toCheck->getResourceC_v2(statId).getParamC_t(param);
				Vector2D rot = point.getRotated(toCheck->getRotC().position);
				return pos + rot;
			}
		}

		float evaluate( Game::Object* other) override
		{
			Vector2D toOther = getAnchor();
			Vector2D posOther = other->getResourceC_v2(statId).getParamC_t(param);
			toOther = getAnchor() - posOther;

			//auto v = toOther.normalised();

			float r = getFromMode(toOther, mode);
			return r;
		}


	};

}