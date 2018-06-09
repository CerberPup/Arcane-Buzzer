#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <String>
#include "Engine.h"

//!Class of Menu object
class Menu
{
private:
	//!View for menu
	sf::View view;
	//!Font used in menu
	sf::Font font;
	//!Window size;
	sf::Vector2u size;
public:
	Menu();
	~Menu();
	//!Main menu loop
	void Run();
};
