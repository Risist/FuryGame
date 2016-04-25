#pragma once
#include "EvaluateBase.h"

namespace Evaluate
{

	class Stat_v2 : public Base
	{
	public:
		enum Param
		{
			positionX,
			positionY,
			positionLenght,
			positionLenghtSq,

			velocityX,
			velocityY,
			velocityLenght,
			velocityLenghtSq,

			forceX,
			forceY,
			forceLenght,
			forceLenghtSq,

			inverseMass,
			resetVelocity,
			resetForce
		}param;
		float getParam(const Resource<Vector2D>& resource, Param param)
		{
			switch (param)
			{
			case positionX:
				return resource.position.x;
			case positionY:
				return resource.position.y;
			case positionLenght:
				return resource.position.getLenght();
			case positionLenghtSq:
				return resource.position.getLenghtSq();


			case velocityX:
				return resource.velocity.x;
			case velocityY:
				return resource.velocity.y;
			case velocityLenght:
				return resource.velocity.getLenght();
			case velocityLenghtSq:
				return resource.velocity.getLenghtSq();

			case forceX:
				return resource.force.x;
			case forceY:
				return resource.force.y;
			case forceLenght:
				return resource.force.getLenght();
			case forceLenghtSq:
				return resource.force.getLenghtSq();

			case inverseMass:
				return resource.inverseMass;
			case resetVelocity:
				return resource.resetVelocity;
			case resetForce:
				return resource.resetForce;
			}
		}


		Stat_v2(size_t _statId = Game::Event::pos, Param _param = positionX)
			: param(_param), statId(_statId)
		{

		}



		float evaluate(Game::Object * obj) override
		{
			return getParam(obj->getResourceC_v2(statId), param);
		}


		size_t statId;


	};

}

