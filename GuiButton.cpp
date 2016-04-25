#include "GuiButton.h"
#include "control.h"

namespace Gui
{

	Button::Button(const Vector2f& _pos,
		const Vector2f& _wh,
		const string& str,
		const sf::Color& _clIn,
		const sf::Color& _clOn,
		const sf::Color& _clOut,
		const sf::Color& _clTxt,
		size_t txtSize)
		: Base(_pos), wh(_wh)
		, clIn(_clIn), clOut(_clOut), clOn(_clOn)
	{

		txt << str;
		txt.txt.setCharacterSize(txtSize);

		txt.txt.setColor(_clTxt);
	}

	void Button::update( RenderWindow& wnd)
	{
		ConvexShape sh(4);
		sh.setPoint(0, getPosA());
		sh.setPoint(1, getPosA() + Vector2f(wh.x, 0) );
		sh.setPoint(2, getPosA() + Vector2f(wh.x, wh.y) );
		sh.setPoint(3, getPosA() + Vector2f(0, wh.y) );

		sh.setFillColor( isColl(wnd) ? clOn : clIn);
		sh.setOutlineColor(clOut);

		Base::draw(wnd, sh);

		txt.updatePos(getPosA());
		txt.update(wnd);

	}

	bool Button::isPressed(RenderWindow& wnd, sf::Mouse::Button button, sf::Keyboard::Key key, float cd)
	{
		static Control::Timer timer;
		return timer.isReadyRestart(cd) &&
			( (isColl(wnd) && sf::Mouse::isButtonPressed(button)) || sf::Keyboard::isKeyPressed(key) );
	}

	bool Button::isColl(sf::RenderWindow& wnd)
	{
		Vector2f mousePos = (Vector2f)Mouse::getPosition(wnd) - Vector2f(wnd.getSize().x * 0.5, wnd.getSize().y * 0.5); // Vector2f(300,300);
		return	getPosA().x < mousePos.x &&		getPosA().x + wh.x > mousePos.x &&
				getPosA().y < mousePos.y &&		getPosA().y + wh.y > mousePos.y;
	}
	
}