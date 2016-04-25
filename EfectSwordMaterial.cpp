#include "EfectSwordMaterial.h"


EfectSwordMaterial::EfectSwordMaterial(int _idResX, int _idResY, float _ratioX, float _ratioY, sf::Sprite *_anchorObject, float _addictionalRotation, const Vector2D& _anchorPoint)
	:idResX(_idResX), idResY(_idResY), ratioX(_ratioX), ratioY(_ratioY), anchorObject(_anchorObject), anchorPoint(_anchorPoint), addictionalRotation(_addictionalRotation)
{
}


void EfectSwordMaterial::onInteract(const Vector2D& force, size_t resId, Game::Object*causer)
{
	Efect::onInteract(force,resId, causer);

	if (resId == pos)
	{
		Vector2D _anchorPoint = anchorPoint;
		if (anchorObject != nullptr)
		{
			_anchorPoint.rotate(anchorObject->getRotation());
			_anchorPoint += anchorObject->getPosition();
		}

		if (idResY >= 0)
		{ //y
			Vector2D toCollider = _anchorPoint  - colliderInfo->collider.center;

			float alfa = toCollider.angle(force.prep()) - 90 + addictionalRotation;
			float cosinus = cos(alfa *M_PI / 180);
			getResY().addForce(cosinus * ratioY);
		}
		if (idResX >= 0)
		{ // x
			Vector2D toCollider = _anchorPoint - colliderInfo->collider.getColliderAccordingToSprite(*anchorObject).center;

			float alfa = toCollider.angle(force.prep()) + addictionalRotation;
			float cosinus = cos(alfa *M_PI / 180);
			//cout << "cosinus: " << cosinus << "\n";

			getResX().addForce(cosinus * ratioX);
		}
	}
}