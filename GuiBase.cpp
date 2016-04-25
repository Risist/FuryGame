#include "GuiBase.h"


namespace Gui
{
	Base::Base(const Vector2f& _pos)
		: pos(_pos), hidden(false), relativeTo(false)
	{
		updatePos(pos);
	}


	void Base::draw(RenderWindow& wnd, Drawable& sp)
	{
		Transform transform;

		// neutralize window transform
		if (relativeTo == false)
		{
			View view = wnd.getView();
			transform.translate(view.getCenter());
			transform.rotate(view.getRotation());
			transform.scale(Vector2f(view.getSize().x / wnd.getSize().x, view.getSize().y / wnd.getSize().y));
		}

		// display
		wnd.draw(sp, RenderStates(transform));
	}

}