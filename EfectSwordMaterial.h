#pragma once
#include "GameWorld.h"

class EfectSwordMaterial : public Game::Efect
{
public:
	EfectSwordMaterial(int idResX = 0, int idResY = 0, float ratioX = 1, float ratioY = 1, sf::Sprite *anchorObject = nullptr, float addictionalRotation = 0, const Vector2D& anchorPoint = Vector2D() );

	void onInteract(const Vector2D& v, size_t resId, Game::Object*causer) override;

	float addictionalRotation;
	float ratioX, ratioY;
	sf::Sprite *anchorObject;
	Vector2D anchorPoint;

	int idResX, idResY;
	Resource<float>& getResX()
	{
		return getOwner()->getResource_f(idResX);
	}
	Resource<float>& getResY()
	{
		return getOwner()->getResource_f(idResY);
	}
};

