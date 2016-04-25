#include "GuiMenu.h"

namespace Gui
{

	Menu::Menu(const Vector2f pos) : Base(pos)
	{
	}

	Menu::~Menu()
	{
		for each(Base* it in el)
		{
			delete it;
		}
	}

	void Menu::initOut()
	{
		for each(Base *it in el)
			it->initOut();
	}

	bool Menu::isColl(RenderWindow& wnd) const
	{
		for each (Base*it in el)
			if ( it->isColl(wnd) && it->hidden == false)
			{
				return true;
			}
		return false;
	}

	void Menu::update(RenderWindow& wnd)
	{
		for each(Base *it in el)
			if ( it->hidden == false) // update an element if is not hidden
		{
			it->updatePos(posA);
			it->update(wnd);
		}
	}
	void Menu::updateHidden(bool s)
	{
		for each(Base *it in el)
			it->updateHidden(s);
	}

	void Menu::add(Base * s, bool hidden, bool relativeTo)
	{
		el.push_back(s);
		s->setHidden(hidden);
		s->relativeTo = relativeTo;
	}

	void Menu::clear()
	{
		for (int i = 0; i < el.size(); ++i)
			if (el[i] != nullptr)
			{
				delete el[i];
			}
		el.clear();
	}
}
