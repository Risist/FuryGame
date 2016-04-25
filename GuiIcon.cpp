#include "GuiIcon.h"


namespace Gui
{
	Icon::Icon(size_t id, Vector2f const& _pos, float rot, const Vector2f& scale)
		: Base(_pos)
	{
		setTexture(id);
		sp.setRotation(rot);
		sp.setScale(scale);
	}
	Icon::Icon(const Texture& ts, Vector2f const& pos, float rot, const Vector2f& scale)
	{
		setTexture(ts);
		sp.setPosition(pos);
		sp.setRotation(rot);
		sp.setScale(scale);
	}

	void Icon::update(RenderWindow& wnd)
	{
		sp.setPosition(posA);
		draw(wnd,sp);
	}
}
