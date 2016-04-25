#pragma once
#include "GuiBase.h"
#include <string>
#include <sstream>

using namespace std;

namespace Gui
{
	class Text : public Base
	{
	public:
		Text( const string& str = "", 
			const Vector2f& pos = Vector2f(),
			const Color& color = Color::Black,
			size_t size = 30 );

		void update(RenderWindow& wnd) override;


		Text& operator<<(int s)
		{
			std::ostringstream stream;
			stream << s;
			str += stream.str();

			return *this;
		}
		Text& operator<<(float s)
		{
			std::ostringstream stream;
			stream << s;
			str += stream.str();

			return *this;
		}
		Text& operator<<(const std::string& s)
		{
			str += s;
			return *this;
		}

		Text& clear()
		{
			str = "";
			return *this;
		}

		// graphical representation of text
		sf::Text txt;
		// what is to write
		string str;

		// static part
	private:
		static Font font;
	public: 
		static void initFont(const string& path);

	};

}

