#include "ControlMouseDrag.h"


namespace Control
{
	MouseDrag::MouseDrag(bool _inWorldCoord, Base *_ctrlLock, Base *_ctrlUnlock, const Vector2D& _lockedPoint)
		: inWorldCoord(_inWorldCoord), ctrlLock(_ctrlLock), ctrlUnlock(_ctrlUnlock), lockedPoint(_lockedPoint),
		locked(false)
	{
	}
	MouseDrag::~MouseDrag()
	{
		if (ctrlLock != nullptr)
			delete ctrlLock;
		if (ctrlUnlock != nullptr)
			delete ctrlUnlock;
	}

	Vector2D MouseDrag::getDiffirence( RenderWindow& wnd, const Vector2D& offset)
	{
		if (locked == false)
		{
			if (ctrlLock != nullptr && ctrlLock->isReady())
			{
				lockedPoint = (Vector2f)Mouse::getPosition(wnd) + offset;
				
				if (inWorldCoord == true)
				{
					lockedPoint -= (Vector2D)wnd.getView().getCenter();
					lockedPoint.rotate( wnd.getView().getRotation() );
				}

				locked = true;
			}
		}
		else if (ctrlUnlock != nullptr && ctrlUnlock->isReady())
			locked = false;

		//cout << lockedPoint.x << " " << lockedPoint.y << "\n";
		return (Vector2f)Mouse::getPosition(wnd) - lockedPoint;
	}

	Vector2D MouseDrag::lockMouseOnWindow(RenderWindow& wnd, const Vector2D& freeArea)
	{
		// get desired position
		Vector2D mousePos = (Vector2f)Mouse::getPosition(wnd);
		// clamp in x axes
		if (mousePos.x > wnd.getSize().x - freeArea.x)
			mousePos.x -= wnd.getSize().x - freeArea.x;
		else if (mousePos.x < freeArea.x)
			mousePos.x += wnd.getSize().x - freeArea.x;

		// clamp in y axes
		if (mousePos.y > wnd.getSize().y - freeArea.y)
			mousePos.y -= wnd.getSize().y -freeArea.y;
		else if (mousePos.y < freeArea.y)
			mousePos.y += wnd.getSize().y - freeArea.y;

		// set new position on mouse
		Mouse::setPosition((Vector2i)mousePos, wnd);
		return mousePos;
	}


}


