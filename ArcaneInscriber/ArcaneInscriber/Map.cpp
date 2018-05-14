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
		for (int i = 0; i < 33; i++)
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
				if (c == 14)
					textureRect = { 176, 16, 16, 16 };
				if (c == 15)
					textureRect = { 128, 48, 16, 16 };
				if (c == 16)
					textureRect = { 144, 48, 16, 16 };
				if (c == 17)
					textureRect = { 160, 32, 16, 16 };
				if (c == 18)
					textureRect = { 176, 32, 16, 16 };
				if (c == 19)
					textureRect = { 192, 32, 16, 16 };
				if (c == 20)
					textureRect = { 160, 48, 16, 16 };
				if (c == 21)
					textureRect = { 176, 48, 16, 16 };
				if (c == 22)
					textureRect = { 192, 48, 16, 16 };
				if (c == 23)
					textureRect = { 208, 32, 16, 16 };
				if (c == 24)
					textureRect = { 208, 48, 16, 16 };
				if (c == 51)
					textureRect = { 128, 80, 16, 16 };
				if (c == 52)
					textureRect = { 128, 96, 16, 16 };
				if (c != 0 && c != 99)
				{
					if(c > 50)
						mapTiles.push_back(new Tile(pos, size, "tiles", textureRect, false));
					else
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