#include "Menu.h"
#include "Engine.h"

using namespace sf;
using namespace std;

Menu::Menu()
{
	Engine::state = Engine::State::EXIT;

	if (!font.loadFromFile("Resources/Pixeled.ttf"))
	{
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}

	Engine::state = Engine::State::MAINMENU;

	size = Engine::window.getSize();
}

Menu::~Menu()
{
}

void Menu::Run()
{
	Text title("Naked Archer King", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(size.x / 2 - title.getGlobalBounds().width / 2, size.y / 4);
	title.setFillColor(Color(255,255,255,140));

	const short int options = 2;

	Text texts[options];

	string str[] = { "Play","Exit" };
	for (int i = 0; i < options; i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(65);

		texts[i].setString(str[i]);
		texts[i].setPosition(size.x / 2 - texts[i].getGlobalBounds().width / 2, size.y / 2 + i * 120);
	}

	while (Engine::state == Engine::State::MAINMENU)
	{
		Vector2f mouse(Mouse::getPosition(Engine::window));
		Event event;

		while (Engine::window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				Engine::state = Engine::State::EXIT;

			else if (texts[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				Engine::state = Engine::State::EXIT;
			}
			else if (texts[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
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