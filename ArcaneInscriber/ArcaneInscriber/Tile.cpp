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
		sprite.setTextureRect(_textureRect);/*
		sprite.setOrigin(_spriteOrigin.x, _spriteOrigin.y);
		sprite.setScale(_spriteScale.x, _spriteScale.y);*/
	}
}

Tile::~Tile()
{
}
