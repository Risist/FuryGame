#pragma once
#include "GameState.h"
#include <SFML\Audio.hpp>
#include "gui.h"
#include "GamePlayer.h"

namespace El
{
	class StateNewBorn : public Game::State
	{
	public:
		StateNewBorn();

		void onInit() override;
		void onExit() override;

		Game::State* onUpdate(RenderWindow& wnd, Camera& cam, float dt) override;
		
		static sf::Music whisper, oneDay;
		static bool whisper_loaded;
		bool oneDay_archived;
		vector<CircleCollider> mapCollider;
		Control::Timer tSpawn;

		Game::Player *player;
		Gui::Text *txtScore;

		Gui::ProgresBar *pbRespawn;

		void spawnNpc();
	};

}

