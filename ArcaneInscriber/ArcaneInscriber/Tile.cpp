#include "Tile.h"
#include "Engine.h"

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Tile::Tile(sf::Vector2f _pos, sf::Vector2f _size, std::string _texture, sf::IntRect _textureRect) :Physics(_pos, _size)
{
	if (_texture != "") {
		sprite.setTexture(*Engine::getTexture(_texture));
		sprite.setTextureRect(_textureRect);
		//sprite.setOrigin(_pos.x, _pos.y);
		sprite.setPosition(_pos.x, _pos.y);
		sprite.setScale(2, 2);
	}
}

Tile::~Tile()
{
}
