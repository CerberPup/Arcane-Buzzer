#include <iostream>
#include <SFML\Graphics.hpp>
#include "Logger.cpp"


using namespace std;

int main() {
	sf::VideoMode t = sf::VideoMode::getDesktopMode();
	Logger::log("Rozmiar ekranu", t.width, t.height);
	getchar();
}