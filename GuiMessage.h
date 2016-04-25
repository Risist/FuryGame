#pragma once
#include "GuiMenu.h"
#include "GuiText.h"
#include <queue>
#include "control.h"

namespace Gui
{
	class Message : public Gui::Menu
	{
	public:
		Message(const Vector2D& positon = Vector2D(), const Color& txtColor = Color::White, size_t txtSize = 25 );

		void update(sf::RenderWindow& wnd) override;
		void addTxt(const string& txt, float displayPeriod)
		{
			queueTxt.push(make_pair(txt, displayPeriod));
		}

		Gui::Text *txtMain;
		
		queue< pair<string, float> > queueTxt;
		Control::Timer timerNext;
	};

}

