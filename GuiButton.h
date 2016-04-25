#pragma once
#include "GuiText.h"

namespace Gui
{
	class Button : public Base
	{
	public:
		Button(const Vector2f& pos = Vector2f(),
			const Vector2f& wh = Vector2f(),
			const string& str = "",
			const sf::Color& clIn = sf::Color::Black,
			const sf::Color& clOn = sf::Color(150, 150, 150),
			const sf::Color& clOut = sf::Color::Black,
			const sf::Color& clTxt = sf::Color::White,
			size_t txtSize = 20);

		void update(sf::RenderWindow& wnd);

		bool isPressed(RenderWindow& wnd, sf::Mouse::Button button = sf::Mouse::Left, sf::Keyboard::Key key = sf::Keyboard::Unknown, float cd = 0.2f);
		bool isColl(sf::RenderWindow& wnd);

		sf::Vector2f wh;
		sf::Color clIn, clOut, clOn;
		Text txt;
	};

	
}