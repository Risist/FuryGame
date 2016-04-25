#include "GuiText.h"


namespace Gui
{
	Font Text::font;

	Text::Text( const string& _str, const Vector2f& pos, const Color& color, size_t size)
		: str(_str), Base(pos)
	{
		txt.setColor(color);
		txt.setCharacterSize(size);
		txt.setFont(font);
	}

	void Text::update(RenderWindow& wnd)
	{
		txt.setString(str);
		txt.setPosition(getPosA());
		
		draw(wnd, txt);
	}

	void Text::initFont(const string& path)
	{
		font.loadFromFile(path);
	}

}
