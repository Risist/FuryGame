#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2D.h"
using namespace sf;


class Camera : public sf::View
{
public:
	Camera();
	void create(const sf::Vector2f& size, const sf::Vector2f& center = sf::Vector2f());

	// Using
	void draw(const sf::Drawable& s)
	{
		ts.draw(s);
	}
	void draw(sf::Vertex *v, unsigned int vCount, sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default)
	{
		ts.draw(v, vCount, type, states);
	}
	void draw(sf::RenderWindow& wnd, const sf::Vector2f& pos = sf::Vector2f());


	//Center
	void addCenter(const sf::Vector2f& s)
	{
		setCenter(getCenter() + s);
	}
	void addCenter(float x, float y)
	{
		addCenter(sf::Vector2f(x, y));
	}

	// Scale
	void setScale(float s)
	{
		zoom(1 / lastScale);
		lastScale = s;
		zoom(lastScale);
	}
	float getScale()
	{
		return lastScale;
	}

	//
	void setVis(float s)
	{
		vis = s;
	}
	void addVis(float s)
	{
		vis += s;
	}
	float getVis()
	{
		return vis;
	}

	//
	void setDarkness(float s)
	{
		darkness = s;
	}
	void addDarkness(float s)
	{
		darkness += s;
	}
	float getDarkness()
	{
		return darkness;
	}

	//
	void setAlpha(float s)
	{
		alpha = s;
	}
	void addAlpha(float s)
	{
		alpha += s;
	}
	float getAlpha()
	{
		return alpha;
	}

	void setBackgroundColor(const Color& cl)
	{
		background = cl;
	}
	const Color& getBackgroundColor()
	{
		return background;
	}

	void follow(sf::Sprite& sp, float addIctionalRotation = 0, float d = 0, bool followPosition = true, bool followRotation = true);
	void follow(const Vector2D& position, float rotation = 0, float addIctionalRotation = 0, float d = 0, bool followPosition = true, bool followRotation = true);


private:
	sf::RenderTexture ts;
	sf::Image im;
	float darkness, alpha, lastScale;
	float vis;
	Color background;
};
