#include "GuiMessage.h"
#include "utility.h"


namespace Gui
{
	Message::Message(const Vector2D& position, const Color& txtColor, size_t txtSize)
		: Menu(position), timerNext()
	{
		add( txtMain = new Text("", Vector2D(), txtColor, txtSize));
	}

	void Message::update(sf::RenderWindow& wnd)
	{
		Menu::update(wnd);

		if (timerNext.isReady())
		{
			if (!queueTxt.empty())
			{
				auto it = queueTxt.front();
				queueTxt.pop();

				txtMain->str = it.first;

				timerNext.time_wait = it.second;
				timerNext.restart();
			}
			else
			{
				timerNext.time_wait = 0;
				timerNext.restart();
			}
		}
	}

}
