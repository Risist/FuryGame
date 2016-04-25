#include "ElStateNewBorn.h"

#include "ElPlayer.h"
#include "ElObstacleTest.h"
#include "ElRotatingDummy.h"
#include "ElEnemy.h"
#include "ElSpirit.h"
#include "ElSpiritWhite.h"

#include "control.h"

extern Game::World world;
extern Camera cam;

Vector2D positionOfMap(50000, 50000);
Vector2D mapRange(0, 1500);

namespace El
{

	sf::Music StateNewBorn::whisper, StateNewBorn::oneDay;
	bool StateNewBorn::whisper_loaded = false; 

	StateNewBorn::StateNewBorn() : tSpawn(2.5f, true, 0, 100000)
	{
	}
	void StateNewBorn::spawnNpc()
	{
		if (randRange(0, 1) < 0.11)
		{
			for (int i = 0; i < 4; i++)
			{
				auto enemy = new Spirit();
				world.push_back(enemy);
				enemy->getRot().position = randRange(0, 360);
				//enemy->getPos().position = Vector2D(600, 1500).getRotated(randRange(0, 360)) + player->getPosC().position;
				enemy->getPos().position = Vector2D(mapRange.x + 650, mapRange.y - 150).getRotated(randRange(0, 360)) + positionOfMap;
			}
		}
		else
		{
			auto enemy = new Enemy(rand() % 5, (El::Player*)player);
			world.push_back(enemy);
			enemy->getRot().position = randRange(0, 360);
			//enemy->getPos().position = Vector2D(600, 1500).getRotated(randRange(0, 360)) + player->getPosC().position;
			enemy->getPos().position = Vector2D(mapRange.x + 400, mapRange.y-350).getRotated(randRange(0, 360)) + positionOfMap;

			enemy->addEfect(new EfectDeathOutOfCollider(&mapCollider));
		}
	}

	void StateNewBorn::onInit()
	{
		Game::State::onInit();

		cam.setBackgroundColor(Color(150, 150, 175));
		cam.setScale(0.95f);
		//cam.setDarkness(0.9);
		//cam.setAlpha(0.75);
		cam.setDarkness(1);
		cam.setAlpha(1);

		oneDay_archived = false;

		if (whisper_loaded == false)
		{
			whisper.openFromFile("Audio\\316797__dimbark1__ghostly-whispers.wav");
			oneDay.openFromFile("Audio\\whisper - the beggining.wav");
			whisper.setLoop(true);
			whisper_loaded = true;

			tsInst.clear();
			tsInst.push_back(_Texture());
			_Texture::deserializeCont("Textures_newBorn.txt");
		}

		// mapCollider
		mapCollider.push_back(CircleCollider( positionOfMap, mapRange.y -50 ));
		

		
		// preinit player
		
		
		player = new Player();
		player->onInit();
		player->getRot().position = 180;
		player->getPos().position = Vector2D(0, 0).getRotated(player->getRotC().position) + positionOfMap;
		player->addEfect(new EfectDeathOutOfCollider(&mapCollider));
		world.push_backNoInit(player);
	
		{
			int n = randRange(5,10);
			for (int i = 0; i < n; ++i)
			{
				auto it = new Dummy();
				world.push_back(it);
				it->getPos().position = Vector2D(randRange(400, 1300), 0).getRotated(randRange(0, 360)) + positionOfMap;
				it->lockedPosition = it->getPosC().position;
			} 
		}
		/*{
			auto it = new RotatingDummy();
			world.push_back(it);
			it->getPos().position = Vector2D(0, 0) + positionOfMap;
			it->lockedPosition = it->getPosC().position;
		}

		/*{
			int n = randRange(0,2);
			for (int i = 0; i < n; ++i)
			{
				auto it = new RotatingDummy();
				world.push_back(it);
				it->getPos().position = Vector2D( randRange(0,1300), 0).getRotated(randRange(0,360) ) + positionOfMap;
				it->lockedPosition = it->getPosC().position;
			}
		}*/

		//for (int i = 0; i < 3; ++i)
			//spawnNpc();

		gui.add( txtScore = new Gui::Text("score", Vector2D(-500,-200), Color::White, 30) );
		gui.add(pbRespawn = new Gui::ProgresBar(Vector2D(-600,-375), Vector2D(1200, 15), Color(150, 50, 60, 75), Color(20, 20, 20, 200)));

		whisper.play();
		tSpawn.restart();
	}
	void StateNewBorn::onExit()
	{
		Game::State::onExit();

		world.clear();
		gui.clear();
		whisper.stop();
		oneDay.stop();

		mapRange = Vector2D(0, 1300);
	}

	Game::State* StateNewBorn::onUpdate(RenderWindow& wnd, Camera& cam, float dt)
	{
		Game::State::onUpdate(wnd, cam, dt);

		//change scale
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			cam.zoom(1.1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			cam.zoom(1/1.1);


		// spawn Enemy
		static Control::Input iAutoResp( sf::Keyboard::O,Control::Input::keyboard, Control::Input::pressed );
		/**/if (player->isAlive())
		{
			txtScore->clear() << "score: " << ((El::Player*)player)->score;
			pbRespawn->setProgres(tSpawn.getTimeDiffirence() / tSpawn.time_wait * 100);

			if (oneDay_archived == false && ((El::Player*)player)->score >= 6)
			{
				whisper.pause();
				oneDay.play();

				oneDay_archived = true;
			}


			if (randRange(0, 1) <  0.00000135 * mapRange.y)
			{
				auto it = new Dummy();
				world.push_back(it);
				it->getPos().position = Vector2D(0, randRange(mapRange.x + mapRange.y*0.25, mapRange.y - 100)).getRotated(randRange(0, 360)) + positionOfMap;
				it->lockedPosition = it->getPosC().position;
			}
			if (tSpawn.isReady() || iAutoResp.isReady())
			{	

				float l = 0;
				for each (auto it in world)
					if (dynamic_cast<Game::Competitor*>(it) != nullptr && it->isAlive())
					{
						l++;
					}
				float ls = 0;
				for each (auto it in world)
					if (dynamic_cast<Spirit*>(it) != nullptr && it->isAlive())
					{
						ls++;
					}

				tSpawn.time_wait = 5. * l + 2.5f + 2.5 * ls;

				for (int i = 0; i < 1; ++i)
					spawnNpc();

				
				tSpawn.restart();
			}
		}/**/
		// opening eyes
		//cam.setDarkness(clamp(cam.getDarkness()*1.0025f + 0.0025f, 0.f, 1.f));
		//cam.setDarkness(clamp(cam.getDarkness()*1.0025f + 0.0025f, 0.f, 1.f));

		{
			mapRange.y *= 1.00005;
			mapCollider.front().range = mapRange.y - 50;
		}

		{
			sf::CircleShape sh(mapRange.y/1300*2500, 10);
			sh.setTexture(&tsInst[11]);
			sh.setPosition(positionOfMap);
			sh.setOrigin(sh.getRadius(), sh.getRadius());
			sh.setFillColor(Color(255, 200, 200, 255));

			cam.draw(sh);
		}
		{
			sf::CircleShape sh(mapRange.y, 60);
			sh.setTexture(&tsInst[8]);
			sh.setPosition(positionOfMap);
			sh.setOrigin(sh.getRadius(), sh.getRadius());
			sh.setFillColor(Color(75, 75,75, 150));

			cam.draw(sh);
		}
		//cam.setDarkness(0.5 * (1 + 1300 / mapRange.y) );

		// show place allowded to go
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			for each(auto it in mapCollider)
				it.display(cam, Color(150, 50, 50, 100));

		// reset mode
		static Control::Input keyRestart(sf::Keyboard::P, Control::Input::keyboard, Control::Input::pressed );
		if (keyRestart.isReady())
			return new StateNewBorn();

		// update gui
		

		world.update(cam, dt);
		cam.draw(wnd);
		return nullptr;
	}

}
