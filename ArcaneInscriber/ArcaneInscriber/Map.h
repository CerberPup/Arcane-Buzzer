#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>
#include "Tile.h"
#include "Engine.h"
#include "Enemy.h"

//!Class representing the map of the game, including background and enemies
class Map
{
private:
	//!Vector of pointers to Tile, representing layers of background
	std::vector<Tile*> background;
public:
	std::vector<Enemy*> enemies;
	//!Vector of pointers to Tile, representing all Tiles bulding the map
	std::vector<Tile*> mapTiles;
	Map();
	//!Draws all membrers of Map that should be visible on the screen
	void Display(sf::Vector2f viewCenter, sf::Vector2f viewSize);
	~Map();
};