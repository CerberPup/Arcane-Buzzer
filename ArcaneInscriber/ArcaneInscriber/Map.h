#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>
#include "Tile.h"
#include "Engine.h"

class Map
{
public:
	std::vector<Tile*> mapTiles;
	Map();
	void Display(sf::Vector2f viewCenter, sf::Vector2f viewSize);
	~Map();
};