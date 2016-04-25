#include "EfectCircleSign.h"


EfectCircleSign::EfectCircleSign(
	float _radius, 
	const Color& _color, const Color& _colorMax,
	sf::Sprite *_connectedTo, float _valueMax,
	Evaluate::Base* _evaluate)
	: radius(_radius), 
	color(_color), colorMax(_colorMax),
	connectedTo(_connectedTo), valueMax(_valueMax),
	evaluate(_evaluate)
{
}
EfectCircleSign::~EfectCircleSign()
{
	if (evaluate != nullptr)
		delete evaluate;
}


void EfectCircleSign::onDisplay(Camera& cam)
{
	Efect::onDisplay(cam);


	Color _color = color;
	if (evaluate != nullptr)
	{
		_color = colorMax;

		float v = evaluate->evaluate(getOwner())/valueMax;
		_color.r += (float)((float)color.r - (float)colorMax.r)*v;
		_color.g += (float)((float)color.g - (float)colorMax.g)*v;
		_color.b += (float)((float)color.b - (float)colorMax.b)*v;
		_color.a += (float)((float)color.a - (float)colorMax.a)*v;
	}


	sf::CircleShape sh;

	sh.setRadius(radius);
	sh.setFillColor(_color);
	sh.setOrigin(sh.getRadius(), sh.getRadius());
	if (connectedTo != nullptr)
		sh.setPosition( connectedTo->getPosition() );
	else sh.setPosition( getOwner()->getPosC().position);

	cam.draw(sh);
}
