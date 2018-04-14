#include "Tile.h"


void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Tile::Tile(sf::Vector2f _pos,sf::Vector2f _size):Physics(_pos,_size)
{

}


Tile::~Tile()
{
}
