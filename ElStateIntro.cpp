#include "ElStateIntro.h"
#include "ElStateNewBorn.h"

extern Camera cam;

namespace El
{
	sf::Music StateIntro::music;
	bool StateIntro::musicLoaded = false;

	StateIntro::StateIntro()
		: resetKey(sf::Keyboard::Space, Control::Input::keyboard, Control::Input::released),
		light(0), timerLight(30, false), newStateGen(false)
	{

	}
	void StateIntro::serialize(ostream& file)
	{

	}
	void StateIntro::deserialize(istream& file)
	{
		XMLloader loader;
		loader.nextLine(file);
		languageCode = loader.load("language" , "none");

		if (musicLoaded == false)
		{
			string audioPath = loader.load("audioPath", "none audio");
			music.openFromFile(audioPath);
			musicLoaded = true;
		}

		loader.nextLine(file);
		while (loader.str() != "\\")
		{
			string txt = loader.load(languageCode, "no Txt");
			float time = loader.load("timeLast", 1.f);

			lyrics->addTxt(txt, time);
			loader.nextLine(file);
		}
	}


	void StateIntro::onInit()
	{
		Game::State::onInit();
		cam.setBackgroundColor(sf::Color::Black);

		

		tsInst.clear();
		tsInst.push_back(_Texture());
		_Texture::deserializeCont("Textures_intro.txt");

		gui.add(lyrics = new Gui::Message(Vector2D(-450,250), Color::White, 28U));
		deserialize("StateIntro.txt");
		/*lyrics->addTxt("The tale begins when darkness were only the one thing", 4.5f);
		//lyrics->addTxt("The tale begins", 1.75f);
		//lyrics->addTxt("When darkness were only the one thing", 2.75f);
		lyrics->addTxt("Nothing else existed", 2.f);
		lyrics->addTxt("There was no time", 2.f);
		lyrics->addTxt("Space seemed to be only an illusion", 3.5f);
		lyrics->addTxt("The universe stayed in this holy order", 4.5f);
		lyrics->addTxt("Without reason and purpose", 3.f);
		lyrics->addTxt("But...", 1.5f);
		lyrics->addTxt("Everything will face their end", 3.25f);
		lyrics->addTxt("Sooner or later", 2.f);
		lyrics->addTxt("But still", 2.f);
		lyrics->addTxt("No matter when...", 2.75f);
		lyrics->addTxt("\n\n                                                               Place For Ester Egg", 0.f);
		*/
		sf::Sprite spGen;
		spGen.setColor(Color::Transparent);
		gen.addParticle("particle_introTale.txt", 750,1,0, spGen);

		light = 0;
		radius = -50;
		music.setPitch(1.15);
		music.stop();
		music.play();
		timerLight.restart();

	}
	void StateIntro::onExit()
	{
		Game::State::onExit();
		gui.clear();
		music.stop();
	}

	Game::State* StateIntro::onUpdate(RenderWindow& wnd, Camera& cam, float dt)
	{
		Game::State::onUpdate(wnd, cam, dt);

		music.setPitch(music.getPitch() - 0.0002675*dt);
		
		
		if (timerLight.isReady())
		{
			light += 0.0075f*dt;
			if (light >= 0.95)
			{
			newState:
				cam.draw(wnd);
				// change to next game state
				// for debuging purposes there is state reset only
				// TODO
				return new StateNewBorn();

			}
			cam.setBackgroundColor(sf::Color::White * light);
		}

		Vector2D v;
		//v = (sf::Vector2f)Mouse::getPosition(wnd);
		//v -= Vector2D( wnd.getSize().x *0.5f, wnd.getSize().y*0.5f);
		//v.x = clamp( v.x*0.5f, -200.f,200.f);

		if (lyrics->txtMain->str == "But...")
			newStateGen = true;

		if (newStateGen)
		{
			radius += 1.36525f * dt;	
		}

		v.x = clamp(radius, -50.f, 2500.f);

		gen.update(dt, sf::Sprite(), v);
		gen.display(cam);
		cam.draw(wnd);

		if (resetKey.isReady())
			goto newState;

		return nullptr;
	}


}
