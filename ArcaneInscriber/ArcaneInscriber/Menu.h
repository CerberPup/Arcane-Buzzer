#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <String>
#include "Engine.h"


class Menu
{
private:
	sf::View view;
	sf::Font font;
	sf::Vector2u size;
public:
	Menu();
	~Menu();
	void Run();
};
