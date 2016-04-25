#pragma once
#include "GuiBase.h"
#include "_Texture.h"

namespace Gui
{
	class Icon : public Base
	{
	public:
		Icon(size_t id, const Vector2f& pos = Vector2f(), float rot = 0, const Vector2f& scale = Vector2f(1,1) );
		Icon(const sf::Texture& ts, const Vector2f& pos = Vector2f(), float rot = 0, const Vector2f& scale = Vector2f(1, 1));


		void update(RenderWindow& wnd) override;

		void setTexture(const sf::Texture& ts, bool resetRect = false)
		{
			sp.setTexture(ts, resetRect);
			sp.setOrigin( sp.getTextureRect().width/2, sp.getTextureRect().height/2);
		}
		void setTexture(size_t id, bool resetRect = false)
		{
			setTexture(tsInst[id], resetRect);
		}


		// a graphical representation of icon
		Sprite sp;
	};
}

