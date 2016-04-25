#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

namespace Gui
{
	class Base
	{
	public:
		Base( const Vector2f& pos = Vector2f() );
		virtual ~Base(){}

		virtual void initOut(){}


		// display and update gui element
		virtual void update(RenderWindow& wnd){}

		// is on collision with the mouse
		virtual bool isColl(RenderWindow& wnd) const
		{
			return false;
		}
		// is the gui element pressed bu mouse?
		virtual bool isPressed( RenderWindow& wnd, Mouse::Button button = Mouse::Left) const
		{
			return isColl(wnd) && Mouse::isButtonPressed(button);
		}

		// set position relative to position of element connected to
		void updatePos(const Vector2f pos = Vector2f())
		{
			posA = Base::pos + pos;
		}


		const Vector2f& getPosA() const
		{
			return posA;
		}

		// position relative to position of element connected to
		Vector2f pos;

		void setHidden( bool s)
		{
			hidden = s;
			updateHidden(s);
		}
		virtual void updateHidden(bool s){}
		
		// used to hide an element
		// default false ( object is updated)
		bool hidden;
		// display gui element using window transform( true )
		// or independed ( false )
		// default false
		bool relativeTo;


	protected:
		void draw(RenderWindow& wnd, Drawable& sp);

		// actual position of gui element
		Vector2f posA; 

	};
}

