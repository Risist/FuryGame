#include "_Texture.h"
#include "GameWorld.h"

#include "GameStateManager.h"
#include "SuState.h"
#include "ElStateIntro.h"
#include "ElStateNewBorn.h"
#include "SlStateGame.h"

using namespace sf;

RenderWindow wnd;
Camera cam;
Game::World world;
Game::StateManager stateManager;
Gui::Message *message;

void init()
{
	wnd.create(VideoMode(1024, 768, 32), "", sf::Style::Default | sf::Style::Fullscreen);
	wnd.setFramerateLimit(60);
	srand(time(nullptr));

	cam.create(Vector2D(wnd.getSize().x, wnd.getSize().y));
	cam.setBackgroundColor(Color(0, 0, 0));
	cam.setDarkness(1);
	cam.setScale(1.25f);

	Gui::Text::initFont("files\\Akv.ttf");

	//stateManager.setState(new Su::State);
	//stateManager.setState(new El::StateIntro);
	stateManager.setState(new El::StateNewBorn);
	//stateManager.setState(new Sl::StateGame);



	gui.initOut();
	
}
void update()
{
	ConvexShape sh(4);
	sh.setFillColor(Color::Black);
	sh.setPoint(0, Vector2D() );
	sh.setPoint(0, Vector2D(wnd.getSize().x,0));
	sh.setPoint(0, Vector2D(wnd.getSize().x, wnd.getSize().y));
	sh.setPoint(0, Vector2D(0,wnd.getSize().y));

	wnd.draw(sh);


	stateManager.onUpdate(wnd, cam, 1 );

	gui.update(wnd);
}
void out()
{
}

int main()
{
	init();

	while (wnd.isOpen())
	{
		Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == Event::Closed ||
				(ev.type == Event::KeyPressed && ev.key.code == sf::Keyboard::Escape))
				wnd.close();
		}
		update();
		wnd.display();
	}
	out();
}
