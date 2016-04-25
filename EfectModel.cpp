#include "EfectModel.h"


EfectModel::EfectModel(const string& _path, sf::Sprite *_connectedTo,
	bool _updateRotation, bool _updatePosition, bool _update,
	float _reloadDelay)
	: path(_path), EfectUpdateModel( nullptr, _connectedTo, _updatePosition, _updateRotation),
	timerReload(_reloadDelay), update(_update), stream(nullptr)
{
}
EfectModel::EfectModel(istream& file, sf::Sprite *_connectedTo,
	bool _updateRotation, bool _updatePosition, bool _update,
	float _reloadDelay)
	: stream(&file), EfectUpdateModel(nullptr, _connectedTo, _updatePosition, _updateRotation),
	timerReload(_reloadDelay), update(_update)
{
}



void EfectModel::onInit()
{
	Efect::onInit();
	EfectUpdateModel::model = &model;
	reloadModel();
}

void EfectModel::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);

	model.draw(cam, connectedTo == nullptr ? sf::Sprite() : *connectedTo );
}
void EfectModel::onUpdate(float dt)
{
	if (update)
		EfectUpdateModel::onUpdate(dt);
	else
		Efect::onUpdate(dt);

	if (timerReload.time_wait > 0 && timerReload.isReady())
		reloadModel();
}

void EfectModel::reloadModel()
{
	if (stream != nullptr)
	{
		model.deserialize(*stream);
	}
	else if (path != "")
		model.deserialize(path);
}