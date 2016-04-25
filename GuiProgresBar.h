#pragma once

#include "GuiMenu.h"
#include "GuiButton.h"
#include "utility.h"

namespace Gui
{
	class ProgresBar : public Menu
	{
	public:
		ProgresBar(const Vector2f& pos = Vector2f(), const Vector2f& wh = Vector2f(), const sf::Color& clUp = Color::Red, const sf::Color& clDown = Color::Black, float pAc = 100, float pMax = 100, const sf::Vector2f& side = sf::Vector2f(1, 0));
		
		void update(sf::RenderWindow& wnd);
		void updateProgres();

		void setProgresMax(float s)
		{
			max = s;
		}
		float getProgresMax() const
		{
			return max;
		}

		void setProgres(float s)
		{
			actualy = s;
			updateProgres();
		}
		float getProgres() const
		{
			return actualy;
		}
		void addProgres(float s = 1.f)
		{
			actualy += s;
			if (actualy > max)
				actualy = max;
			updateProgres();
		}

		float getPercent() const
		{
			return  actualy / max * 100;
		}
		float getLost() const
		{
			return max - actualy;
		}
		float getLostPercent() const
		{
			return getLost() / max * 100;
		}

		const sf::Vector2f& getWh() const
		{
			return bDown->wh;
		}
		void setWh(const sf::Vector2f& s)
		{
			bDown->wh = s;
			updateProgres();
		}

		void setSide(const sf::Vector2f& s)
		{
			setSide(s.x, s.y);
		}
		void setSide(float x, float y)
		{
			if (x < 0)
			{
				bDown->pos.x += bDown->wh.x;
				bUp->pos.x += bUp->wh.x;
				bDown->wh.x = -bDown->wh.x;
			}
			if (y < 0)
			{
				bDown->pos.y += bDown->wh.y;
				bUp->pos.y += bUp->wh.y;
				bDown->wh.y = -bDown->wh.y;
			}
			side = sf::Vector2f(x, y);
		}

		float actualy, max;//progres actualy, max
		sf::Vector2f side;
		bool lockProgres;
	private:
		Button *bUp, *bDown;
	};
}