#include "ControlInput.h"
#include <iostream>

namespace Control
{
	Input::Input(int _key_code, key_type _type, key_state _state_requed)
		: key_code(_key_code), type(_type), state_requed(_state_requed)
	{
		state = key_state::nothing;
	}
	string Input::codeToStr(sf::Keyboard::Key key)
	{
		// alfabet
		if (key == sf::Keyboard::A)
			return "A";
		else if (key == sf::Keyboard::B)
			return "B";
		else if (key == sf::Keyboard::C)
			return "C";
		else if (key == sf::Keyboard::D)
			return "D";
		else if (key == sf::Keyboard::E)
			return "E";
		else if (key == sf::Keyboard::F)
			return "F";
		else if (key == sf::Keyboard::G)
			return "G";
		else if (key == sf::Keyboard::H)
			return "H";
		else if (key == sf::Keyboard::I)
			return "I";
		else if (key == sf::Keyboard::J)
			return "J";
		else if (key == sf::Keyboard::K)
			return "K";
		else if (key == sf::Keyboard::L)
			return "L";
		else if (key == sf::Keyboard::M)
			return "M";
		else if (key == sf::Keyboard::N)
			return "N";
		else if (key == sf::Keyboard::O)
			return "O";
		else if (key == sf::Keyboard::P)
			return "P";
		else if (key == sf::Keyboard::R)
			return "R";
		else if (key == sf::Keyboard::S)
			return "S";
		else if (key == sf::Keyboard::T)
			return "T";
		else if (key == sf::Keyboard::U)
			return "U";
		else if (key == sf::Keyboard::W)
			return "W";
		else if (key == sf::Keyboard::X)
			return "X";
		else if (key == sf::Keyboard::Y)
			return "Y";
		else if (key == sf::Keyboard::Z)
			return "Z";
		else if (key == sf::Keyboard::Q)
			return "Q";

		// noumbers
		else if (key == sf::Keyboard::Num0)
			return "0";
		else if (key == sf::Keyboard::Num1)
			return "1";
		else if (key == sf::Keyboard::Num2)
			return "2";
		else if (key == sf::Keyboard::Num3)
			return "3";
		else if (key == sf::Keyboard::Num4)
			return "4";
		else if (key == sf::Keyboard::Num5)
			return "5";
		else if (key == sf::Keyboard::Num6)
			return "6";
		else if (key == sf::Keyboard::Num7)
			return "7";
		else if (key == sf::Keyboard::Num8)
			return "8";
		else if (key == sf::Keyboard::Num9)
			return "9";

		// num pad
		else if (key == sf::Keyboard::Numpad0)
			return "Pad0";
		else if (key == sf::Keyboard::Numpad1)
			return "Pad1";
		else if (key == sf::Keyboard::Numpad2)
			return "Pad2";
		else if (key == sf::Keyboard::Numpad3)
			return "Pad3";
		else if (key == sf::Keyboard::Numpad4)
			return "Pad4";
		else if (key == sf::Keyboard::Numpad5)
			return "Pad5";
		else if (key == sf::Keyboard::Numpad6)
			return "Pad6";
		else if (key == sf::Keyboard::Numpad7)
			return "Pad7";
		else if (key == sf::Keyboard::Numpad8)
			return "Pad8";
		else if (key == sf::Keyboard::Numpad9)
			return "Pad9";

		// arrows
		else if (key == sf::Keyboard::Up)
			return "Up";
		else if (key == sf::Keyboard::Down)
			return "Down";
		else if (key == sf::Keyboard::Left)
			return "Left";
		else if (key == sf::Keyboard::Right)
			return "Right";


		return "Unknown";
	}
	string Input::codeToStr(sf::Mouse::Button button)
	{
		if (button == sf::Mouse::Left)
			return "MouseLeft";
		if (button == sf::Mouse::Left)
			return "MouseMiddle";
		if (button == sf::Mouse::Left)
			return "MouseRight";

		return "Unknown";
	}
	int Input::strToCode(const string& str)
	{
		// alfabet
		if (str == "A")
			return sf::Keyboard::A;
		else if (str == "B")
			return sf::Keyboard::B;
		else if (str == "C")
			return sf::Keyboard::C;
		else if (str == "D")
			return sf::Keyboard::D;
		else if (str == "E")
			return sf::Keyboard::E;
		else if (str == "F")
			return sf::Keyboard::F;
		else if (str == "G")
			return sf::Keyboard::G;
		else if (str == "H")
			return sf::Keyboard::H;
		else if (str == "I")
			return sf::Keyboard::I;
		else if (str == "J")
			return sf::Keyboard::J;
		else if (str == "K")
			return sf::Keyboard::K;
		else if (str == "L")
			return sf::Keyboard::L;
		else if (str == "M")
			return sf::Keyboard::M;
		else if (str == "N")
			return sf::Keyboard::N;
		else if (str == "O")
			return sf::Keyboard::O;
		else if (str == "P")
			return sf::Keyboard::P;
		else if (str == "R")
			return sf::Keyboard::R;
		else if (str == "S")
			return sf::Keyboard::S;
		else if (str == "T")
			return sf::Keyboard::T;
		else if (str == "U")
			return sf::Keyboard::U;
		else if (str == "W")
			return sf::Keyboard::W;
		else if (str == "Y")
			return sf::Keyboard::Y;
		else if (str == "X")
			return sf::Keyboard::X;
		else if (str == "Z")
			return sf::Keyboard::Z;
		else if (str == "Q")
			return sf::Keyboard::Q;

		// noumbers
		else if (str == "0")
			return sf::Keyboard::Num0;
		else if (str == "1")
			return sf::Keyboard::Num1;
		else if (str == "2")
			return sf::Keyboard::Num2;
		else if (str == "3")
			return sf::Keyboard::Num3;
		else if (str == "4")
			return sf::Keyboard::Num4;
		else if (str == "5")
			return sf::Keyboard::Num5;
		else if (str == "6")
			return sf::Keyboard::Num6;
		else if (str == "7")
			return sf::Keyboard::Num7;
		else if (str == "8")
			return sf::Keyboard::Num8;
		else if (str == "9")
			return sf::Keyboard::Num9;

		// num pad
		else if (str == "Pad0")
			return sf::Keyboard::Numpad0;
		else if (str == "Pad1")
			return sf::Keyboard::Numpad1;
		else if (str == "Pad2")
			return sf::Keyboard::Numpad2;
		else if (str == "Pad3")
			return sf::Keyboard::Numpad3;
		else if (str == "Pad4")
			return sf::Keyboard::Numpad4;
		else if (str == "Pad5")
			return sf::Keyboard::Numpad5;
		else if (str == "Pad6")
			return sf::Keyboard::Numpad6;
		else if (str == "Pad7")
			return sf::Keyboard::Numpad7;
		else if (str == "Pad8")
			return sf::Keyboard::Numpad8;
		else if (str == "Pad9")
			return sf::Keyboard::Numpad9;

		// arrows
		else if (str == "Left")
			return sf::Keyboard::Left;
		else if (str == "Right")
			return sf::Keyboard::Right;
		else if (str == "Up")
			return sf::Keyboard::Up;
		else if (str == "Down")
			return sf::Keyboard::Down;

		// mouse
		else if (str == "MouseLeft")
			return sf::Mouse::Left;
		else if (str == "MouseMiddle")
			return sf::Mouse::Middle;
		else if (str == "MouseRight")
			return sf::Mouse::Right;

		return -1; // Unknown key

		// this part dont run right
		int code;
		stringstream stream(str);
		stream >> code;
		return code;

		// TODO other keys
		// if in any sytuation is needed more
		// than that what is just done
	}

	void Input::serialize(ostream& file)
	{
		if (type == keyboard)
			file << "keyboard	";
		else
			file << "mouse	";

		if (state_requed == pressed)
			file << "pressed	";
		else if (state_requed == released)
			file << "released	";
		else if (state_requed == stay)
			file << "stay	";
		else if (state_requed == nothing)
			file << "nothing	";

		string str;
		if (type == keyboard)
			str = codeToStr((sf::Keyboard::Key)key_code);
		else
			str = codeToStr((sf::Mouse::Button)key_code);

		file << str << "	";

	}
	void Input::deserialize(istream& file)
	{
		XMLloader loader;
		loader.nextLine(file);
		string s = loader.load( "type", "keyboard");
		type = s == "keyboard" ? keyboard : mouse;

		s = loader.load("state", "pressed");
		if (s == "pressed")
			state_requed = pressed;
		else if (s == "stay")
			state_requed = stay;
		else if (s == "released")
			state_requed = released;
		else if (s == "nothing")
			state_requed = nothing;

		s = loader.load("code", "A");
		key_code = strToCode(s);
	}

	bool Input::isReady()
	{
		bool b; // key is pressed?
		switch (type)
		{
		case keyboard:
			b = sf::Keyboard::isKeyPressed(getKey());
			break;
		case mouse:
			b = sf::Mouse::isButtonPressed(getKeyM());
			break;

		default:
			std::cout << "error, wrong key type, sended by " << (int)this << "\n";
			return false;
		}

		// update state
		if (b == true)
		{
			if (state == key_state::nothing || state == key_state::released)
				state = key_state::pressed;
			else if (state == key_state::pressed)
				state = key_state::stay;
			// else if( state == key_state::stay )
			//		do_nothing;
		}
		else // if( b == false )
		{
			if (state == key_state::stay)
				state = key_state::released;
			else if (state == key_state::released || state == key_state::pressed)
				state = key_state::nothing;
			// else if( state == key_state::nothing)
			//		do_nothing;
		}

		// return
		if (state_requed == state)
			return true;
		return false;
	}

}