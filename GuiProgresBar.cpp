#include "GuiProgresBar.h"

namespace Gui
{
	ProgresBar::ProgresBar(const Vector2f& _pos, const Vector2f& _wh, const sf::Color& clUp, const sf::Color& clDown, float pAc, float pMax, const sf::Vector2f& _side)
		: lockProgres(true)
	{
		add(bDown = new Button(_pos, _wh, "", clDown, clDown, sf::Color::Black));
		add(bUp = new Button(_pos, _wh, "", clUp, clUp, sf::Color::Black));

		setSide(_side);

		setProgresMax(pMax);
		setProgres(pAc);
	}

	void ProgresBar::update(sf::RenderWindow& wnd)
	{
		Menu::update(wnd);
	}

	void ProgresBar::updateProgres()
	{
		float p = actualy/max;
		if (lockProgres)
			p = clamp(p, 0.f, 1.f);

		bUp->wh = Vector2f(bDown->wh.x* p * abs(side.x) +
		bDown->wh.x * (1 - abs(side.x)),

		bDown->wh.y* p * abs(side.y) +
		bDown->wh.y * (1 - abs(side.y)));
	}


}
