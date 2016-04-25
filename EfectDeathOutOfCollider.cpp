#include "EfectDeathOutOfCollider.h"


EfectDeathOutOfCollider::EfectDeathOutOfCollider(vector<CircleCollider> *_collidersSaveZone, sf::Sprite *_connectedTo, float _damageOut,
	const Control::Input& _inputDebug, const Color& _clDebug )
	: collidersSaveZone(_collidersSaveZone), connectedTo(_connectedTo), inputDebug(_inputDebug), clDebug(_clDebug)
	, damageOut(_damageOut)
{
}



void EfectDeathOutOfCollider::onInit()
{
	Efect::onInit();

}

void EfectDeathOutOfCollider::onUpdate(float dt)
{
	Efect::onUpdate(dt);
	if (collidersSaveZone == nullptr)
		return;

	bool b = false;
	if (connectedTo == nullptr)
	{
		for each(auto &it in *collidersSaveZone)
			if (getOwner()->isOnCollision(it) )
			{
				b = true;
				goto out;
			}
	}
	else
	{
		for each(auto &it in *collidersSaveZone)
			if (getOwner()->isOnCollision(it.getColliderAccordingToSprite(*connectedTo)) )
			{
				b = true;
				goto out;
			}
	}

	out:
	if (b == false)
		getOwner()->onDamage(damageOut);
}
void EfectDeathOutOfCollider::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);
	if (collidersSaveZone == nullptr)
		return;

	if (inputDebug.isReady())
	{
		if (connectedTo != nullptr)
		for each(auto &it in *collidersSaveZone )
			it.getColliderAccordingToSprite(*connectedTo).display(cam, clDebug);
		else
			for each(auto &it in *collidersSaveZone)
				it.display(cam, clDebug);

	}
}
