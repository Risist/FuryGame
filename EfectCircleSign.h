#pragma once
#include "GameWorld.h"

class EfectCircleSign : public Game::Efect
{
public:
	EfectCircleSign(float radius = 0, 
		const Color& color = Color::Black, const Color& colorMax = Color::Black,
		sf::Sprite *connectedTo = nullptr, float valueMax = 100,
		Evaluate::Base* evaluate = nullptr);
	~EfectCircleSign();

	void onDisplay(Camera& cam) override;


	float radius;
	Color color, colorMax;
	float valueMax;
	sf::Sprite *connectedTo;
	Evaluate::Base* evaluate;
};

