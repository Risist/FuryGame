#include "ActionMoveTo.h"


ActionMoveTo::ActionMoveTo(Game::Object **_aim, float _timeDiference, const Vector2D& _radius, 
	const Vector2D& _tolerance, bool _useLayerX, bool _useLayerY, const initializer_list< pair<Action*, float> >& _initializer)
	: aim(_aim), timeDiference(_timeDiference), radius(_radius), tolerance(_tolerance), useLayerX(_useLayerX), useLayerY(_useLayerY)
	, Action(_initializer)
{
}
ActionMoveTo::ActionMoveTo(const Vector2D& _position, const Vector2D& _radius, const Vector2D& _tolerance)
	: aim(nullptr), position(_position), radius(_radius), tolerance(_tolerance)
{
}

void ActionMoveTo::update(float dt)
{
	if (aim != nullptr)
	{
		if (*aim != nullptr)
		{
			Vector2D rad = radius;

			float myRadius = owner->layerCollider.collider.range;
			float enemyRadius = (*aim)->layerCollider.collider.range;

			if (useLayerX)
			{
				rad.x += myRadius;
				rad.y += myRadius;
			}
			if (useLayerY)
			{
				rad.x += enemyRadius;
				rad.y += enemyRadius;
			}

			isDone = owner->moveTo(*aim, timeDiference, rad, tolerance);
		}
	}
	else
	{
		isDone = owner->moveTo(position, radius, tolerance);
	}
}
bool ActionMoveTo::done()
{
	return isDone;
}
/*void ActionMoveTo::reset()
{

}*/