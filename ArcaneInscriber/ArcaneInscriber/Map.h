#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Map
{
private:
	std::fstream mapFile;

public:
	std::vector<Tile*> mapTiles;
	Map();
	void Display(sf::Vector2f viewCenter, sf::Vector2f viewSize, sf::RenderWindow &win);
	~Map();
};