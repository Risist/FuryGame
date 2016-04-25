#pragma once
#include "GameState.h"
#include <SFML\Audio.hpp>

#include "gui.h"
#include "GuiMessage.h"
#include "ParticleGenerator.h"

namespace El
{
	class StateIntro : public Game::State, public ISerializable
	{
	public:
		StateIntro();

		void onInit() override;
		void onExit() override;

		Game::State* onUpdate(RenderWindow& wnd, Camera& cam, float dt) override;

		Control::Input resetKey;
		Control::Timer timerLight;
		Gui::Message *lyrics;

		ParticleGenerator gen;
		bool newStateGen;

		string languageCode;

		void serialize(const string& str)
		{
			ISerializable::serialize(str);
		}
		void serialize(ostream& file) override;
		void deserialize(const string& str)
		{
			ISerializable::deserialize(str);
		}
		void deserialize(istream& file) override;

	private:
		static sf::Music music;
		static bool musicLoaded;
		float light;
		float radius;
	};

}

