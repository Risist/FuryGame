#include "EfectUpdateModel.h"


EfectUpdateModel::EfectUpdateModel(Model *_model, sf::Sprite *_connectedTo, bool _updatePosition, bool _updateRotation)
	: connectedTo(_connectedTo), model(_model), updatePosition(_updatePosition), updateRotation(_updateRotation)
{
}


void EfectUpdateModel::onUpdate(float dt)
{
	Game::Efect::onUpdate(dt);

	if (updatePosition)
		model->pos = getOwner()->getPosC().position;
	if (updateRotation)
		model->rot = getOwner()->getRotC().position;

	if (model == nullptr)
		return;

	if (connectedTo == nullptr)
		model->updateAll();
	else
		model->updateAll(*connectedTo);
}