#include "EfectMaterial.h"


EfectMaterial::EfectMaterial(size_t _resId, Type _type, Efect *_toAct, float _forceRatio)
	: toAct(_toAct), forceRatio(_forceRatio), resId(_resId), type(_type)
{
}

void EfectMaterial::onInteract(float force, size_t resId, Game::Object *causer)
{
	Efect::onInteract(force, resId, causer);

	if (resId != EfectMaterial::resId || type != f || toAct == nullptr)
		return;

	toAct->onInteract(force * forceRatio, resId, causer);
}
void EfectMaterial::onInteract(const Vector2D& force, size_t resId, Game::Object *causer)
{
	Efect::onInteract(force, resId, causer);

	if (resId != EfectMaterial::resId || type != v2 || toAct == nullptr)
		return;

	toAct->onInteract(force * forceRatio, resId, causer);
}