#include "EfectRotateOnCollision.h"


EfectRotateOnCollision::EfectRotateOnCollision(float _force, sf::Sprite *_anchorObject, float _addictionalAngle, const Vector2D& _anchorPoint)
	: force(_force), anchorObject(_anchorObject), anchorPoint(_anchorPoint), addictionalAngle(_addictionalAngle)
{
}



void EfectRotateOnCollision::onInteract(const Vector2D& force, size_t resId, Game::Object *causer)
{
	Game::Efect::onInteract(force, resId, causer);

	if (resId == pos)
	{
		Vector2D _anchorPoint = anchorPoint;
		if (anchorObject != nullptr)
		{
			_anchorPoint.rotate(anchorObject->getRotation());
			_anchorPoint += anchorObject->getPosition();
		}

		Vector2D toCollider = -colliderInfo->collider.getColliderAccordingToSprite(*anchorObject).center + _anchorPoint;

		//float cosinus = -toCollider.prep().dot(force)/ toCollider.getLenght() / force.getLenght();
		float alfa = toCollider.angle(force.prep()) + addictionalAngle;
		float cosinus = cos(alfa *M_PI / 180);
		//cout << "cosinus: " << cosinus << "\n";

		getOwner()->onSwing( cosinus * EfectRotateOnCollision::force);
	}
}