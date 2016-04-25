#pragma once
#include "GuiBase.h"
#include <vector>

using namespace std;

namespace Gui
{

	class Menu : public Base
	{
	public:
		Menu( const Vector2f pos = Vector2f() );
		~Menu();

		void initOut() override;

		void update(RenderWindow& wnd) override;
		bool isColl(RenderWindow& wnd) const override;

		void updateHidden(bool s) override;

		void add(Base* s, bool hidden = false, bool relativeTo = false);
		Base* operator[](size_t id)
		{
			return el[id];
		}

		void clear();

	protected:
		vector<Base*> el;
	};
}

