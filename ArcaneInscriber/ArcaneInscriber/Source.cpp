#include <iostream>
#include <SFML\Graphics.hpp>
#include "Logger.h"
#include "Engine.h"
#include "Game.h"
#include <Windows.h>
#include <map>
#include "Menu.h"


using namespace std;

void splash(Engine &e) {
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf")) {
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}
	sf::Vector2u size = e.window.getSize();
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));
	e.window.setView(view);
	sf::Text title("Naked Archer King", font, 40);
	title.setStyle(sf::Text::Bold);
	title.setPosition(- title.getGlobalBounds().width / 2, -160);
	sf::Color c(255,255,255, 0);
	title.setFillColor(c);
	for (int i = 0; i < 46; i++)
	{
		e.window.clear(sf::Color(23, 23, 23, 255));
		e.window.draw(title);
		e.window.display();
		c.a += 3;
		Sleep(30);
		title.setFillColor(c);
	}
}

void initResources() {
	try {
		Engine::setTexture("Resources/City.png", "City");
		Engine::setTexture("Resources/characters.png", "playerModels");
		Engine::setTexture("Resources/Tiles.png", "tiles");
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}
}

int main() {
	sf::VideoMode t = sf::VideoMode::getDesktopMode();
	//LOG("Rozmiar ekranu", t.width, t.height);
	Engine e(t.width, t.height);
	initResources();

	while (e.window.isOpen()) {
		switch (Engine::state)
		{
		case Engine::State::SPLASH: {
			//animacja na starcie
			splash(e);
			Engine::state = Engine::State::MAINMENU;
			break;
		}
		case Engine::State::MAINMENU: {
			Menu menu;
			menu.Run();
			//Menu. Po wcisnieciu start zmienia state na game
			
			break;
		}
		case Engine::State::GAME: {
			Game gra;
			gra.Run();
			Engine::state = Engine::State::MAINMENU;
			//glowna petla gry. Osobne watki na przechwytywanie inputu, draw frame, kolizje, animacje
			break;
		}
		case Engine::State::EXIT: {
			Engine::window.close();
			break;
		}
		default:
			break;
		}
	}
}