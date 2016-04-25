#pragma once
#include "ControlBase.h"
#include <SFML\Graphics.hpp>

namespace Control
{
	class Timer : public Base
	{
	public:
		Timer(float time_wait = 1.f, bool restart = true, float time_add = 0, float time_init = 0);

		bool isReady() override;

		// to manual use
		
		// returnes true if is ready
		bool isReady(float time);
		// returnes true if is ready
		// if yes, resets timer
		bool isReadyRestart(float time);
		bool isReadyCheck();

		// returnes time elapsed from last reset
		float getTimeDiffirence() const
		{
			float r = clock.getElapsedTime().asSeconds();
			return r - last_time;
		}
		// resets the timer
		void restart()
		{
			last_time = clock.getElapsedTime().asSeconds();
		}

		// if is ready should i restart timer?
		bool restart_on_ready;
		// time_wait - cooldown
		// last_time - time when timer was last time reseted
		// time_add - how much cooldown is increased every frame
		float time_wait, last_time, time_add;
	private:
		static sf::Clock clock;
	};

}

