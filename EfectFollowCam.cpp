#include "EfectFollowCam.h"


EfectFollowCam::EfectFollowCam(sf::Sprite * _connectedTo, float _addictionalRotation, float _cameraOffset, bool _updatePosition, bool _updateRotation)
	: connectedTo(_connectedTo), addictionalRotation(_addictionalRotation), cameraOffset(_cameraOffset), updatePosition(_updatePosition), updateRotation(_updateRotation)
{
}


void EfectFollowCam::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);
	if (connectedTo != nullptr)
	{
		cam.follow(*connectedTo, addictionalRotation, cameraOffset, updatePosition, updateRotation);

	}
}