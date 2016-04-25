#pragma once
#include "ControlBase.h"
#include "Vector2D.h"

namespace Control
{
	class MouseDrag
	{
	public:
		MouseDrag( bool inWorldCoord = false, Base *ctrlLock = nullptr , Base *ctrlUnlock = nullptr, const Vector2D& lockedPoint = Vector2D() );
		~MouseDrag();
		Vector2D getDiffirence( RenderWindow& wnd, const Vector2D& offset = Vector2D() );

		static Vector2D lockMouseOnWindow(sf::RenderWindow& wnd, const Vector2D& freeArea = Vector2D());

		
		
		// a point from where is counted the diffirence
		Vector2D lockedPoint;
		
		// if equal to nullptr never do it automatically
		Base *ctrlLock, *ctrlUnlock;
		bool inWorldCoord;

	private:
		bool locked;
	};
}
