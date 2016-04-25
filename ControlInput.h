#pragma once
#include "ControlBase.h"
#include "XMLloader.h"
#include "SFML\Window.hpp"

namespace Control
{
	class Input : public Base
	{
	public:
		enum key_type
		{
			keyboard,
			mouse,
			count
		};
		enum key_state
		{
			pressed,
			stay,
			released,
			nothing
		};
		Input(int key_code, key_type type, key_state state_requed = key_state::stay);
		Input(sf::Keyboard::Key key = sf::Keyboard::Unknown)
			: key_code(key), type(key_type::keyboard), state_requed(key_state::stay), state(key_state::nothing)
		{

		}
		Input(sf::Mouse::Button key)
			: key_code(key), type(key_type::mouse), state_requed(key_state::stay), state(key_state::nothing)
		{

		}

		static int strToCode(const string& s);
		static string codeToStr(sf::Keyboard::Key key);
		static string codeToStr(sf::Mouse::Button button);

		void serialize(const string& path)
		{
			ISerializable::serialize(path);
		}
		void serialize(ostream& file);
		void deserialize(const string& path)
		{
			ISerializable::deserialize(path);
		}
		void deserialize(istream& file);

		bool isReady();

		void setKey(int s)
		{
			key_code = s;
		}
		sf::Keyboard::Key getKey() const
		{
			return (sf::Keyboard::Key)key_code;
		}
		sf::Mouse::Button getKeyM() const
		{
			return (sf::Mouse::Button)key_code;
		}

		key_state getCurrentState()
		{
			return state;
		}

	private:
		key_type type;
		key_state state, state_requed;
		int key_code;
	};
}

