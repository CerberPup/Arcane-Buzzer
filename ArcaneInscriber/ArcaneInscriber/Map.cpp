#include "Map.h"

Map::Map()
{
	std::ifstream mapFile;
	mapFile.open("Resources/Map.txt", std::ios::in);
	sf::Vector2f size = { 32, 32 };
	sf::Vector2f pos;
	sf::IntRect textureRect;
	int c = 0;
	int j = 0;
	if (mapFile.good()) {
		for (int i = 0; i < 32; i++)
		{
			j = 0;
			do
			{
				mapFile >> c;
				pos.y = i * 32;
				pos.x = j * 32;
				if (c == 11)
					textureRect = { 112, 32, 16, 16 };
				if (c == 12)
					textureRect = { 128, 32, 16, 16 };
				if (c == 13)
					textureRect = { 144, 32, 16, 16 };
				/*if (c == 'd')
					textureRect = { 112, 48, 16, 16 };
				if (c == 'e')
					textureRect = { 128, 48, 16, 16 };
				if (c == 'f')
					textureRect = { 144, 48, 16, 16 };
				if (c == 'g')
					textureRect = { 160, 32, 16, 16 };
				if (c == 'h')
					textureRect = { 176, 32, 16, 16 };
				if (c == 'i')
					textureRect = { 192, 32, 16, 16 };
				if (c == 'j')
					textureRect = { 160, 48, 16, 16 };
				if (c == 'k')
					textureRect = { 176, 48, 16, 16 };
				if (c == 'l')
					textureRect = { 192, 48, 16, 16 };
				if (c == 'm')
					textureRect = { 208, 32, 16, 16 };
				if (c == 'n')
					textureRect = { 208, 48, 16, 16 };
				if (c == 'p')
					textureRect = { 128, 80, 16, 16 };
				if (c == 'r')
					textureRect = { 128, 96, 16, 16 };*/
				if (c != 0 && c != 99)
				{
					mapTiles.push_back(new Tile(pos, size, "tiles", textureRect));
				}
				j++;
			} while (c != 0);
		}
	}
	mapFile.close();
}

void Map::Display(sf::Vector2f viewCenter, sf::Vector2f viewSize)
{
	for (Tile* tile : mapTiles)
	{
		if ((tile->getPos().x + tile->getRect().width > (viewCenter.x - viewSize.x / 2)) && (tile->getPos().x < (viewCenter.x + viewSize.x / 2)))
		{
			if ((tile->getPos().y > (viewCenter.y - viewSize.y / 2)) && (tile->getPos().y < (viewCenter.y + viewSize.y / 2)))
			{
				Engine::window.draw(*tile);
			}
		}
	}
}

Map::~Map()
{

}