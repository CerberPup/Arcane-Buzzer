#include <iostream>
#include <SFML\Graphics.hpp>
#include "Logger.cpp"
#include "Engine.h"



using namespace std;

int main() {
	sf::VideoMode t = sf::VideoMode::getDesktopMode();
	LOG("Rozmiar ekranu", t.width, t.height);
	Engine e(t.width, t.height);

	while (e.window.isOpen()) {
		switch (Engine::state)
		{
		case Engine::State::SPLASH: {
			//animacja na starcie
			Engine::state = Engine::State::MAINMENU;
			break;
		}
		case Engine::State::MAINMENU: {
			//Menu. Po wcisnieciu start zmienia state na game
			break;
		}
		case Engine::State::GAME: {
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