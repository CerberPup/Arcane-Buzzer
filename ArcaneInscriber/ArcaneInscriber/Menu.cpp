#include "Menu.h"
#include "Engine.h"

using namespace sf;
using namespace std;

Menu::Menu()
{
	Engine::state = Engine::State::EXIT;
	if (!font.loadFromFile("Resources/Pentagram.ttf"))
	{
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}
	sf::Vector2u size = Engine::window.getSize();
	view = View(sf::Vector2f(0,0),sf::Vector2f(size.x, size.y));
	Engine::window.setView(view);

	Engine::state = Engine::State::MAINMENU;

	size = Engine::window.getSize();
}

Menu::~Menu()
{
}

void Menu::Run()
{
	Text title("Naked Archer King", font, 40);
	title.setStyle(Text::Bold);
	title.setPosition(size.x / 2 - title.getGlobalBounds().width / 2, -160);
	title.setFillColor(Color(255,255,255,140));

	bool fullscreen = false;

	const short int options = 3;

	Text texts[options];

	string str[] = { "Play","Fullscreen","Exit" };
	for (int i = 0; i < options; i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(40);

		texts[i].setString(str[i]);
		texts[i].setPosition(size.x / 2 - texts[i].getGlobalBounds().width / 2, size.y / 2 + i * 70);
	}

	while (Engine::state == Engine::State::MAINMENU)
	{
		Vector2f mouse (Engine::window.mapPixelToCoords(Mouse::getPosition(Engine::window)));
		Event event;

		while (Engine::window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				view.setSize(event.size.width, event.size.height);
				Engine::window.setView(view);
			}

			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				Engine::state = Engine::State::EXIT;

			else if (texts[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
					Engine::state = Engine::State::EXIT;
			}
			else if (texts[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				fullscreen = !fullscreen;
				Engine::toggleFullScreen(fullscreen);
				view.setSize(sf::Vector2f(Engine::window.getSize()));
				Engine::window.setView(view);
				//Engine::setStyle(sf::Style::Fullscreen);
			}
			else if (texts[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				Engine::state = Engine::State::GAME;
			}
		}
		for (int i = 0; i < options; i++) {
			if (texts[i].getGlobalBounds().contains(mouse))
			{
				texts[i].setFillColor(Color(255, 255, 255, 200));
			}
			else 
			{ 
				texts[i].setFillColor(Color(255,255,255,140));
			}
		}

		Engine::window.clear(Color(23,23,23,255));
		Engine::window.draw(title);

		for (int i = 0; i < options; i++)
		{
			Engine::window.draw(texts[i]);
		}

		Engine::window.display();
	}
}