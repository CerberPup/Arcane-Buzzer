#pragma once
#include <string>
#include "Entity.h"
#include "Physics.h"
#include <SFML\Graphics.hpp>
class Tile :
	public Entity,
	public sf::Transformable,
	public sf::Drawable,
	public Physics
{
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Tile();
	Tile(sf::Vector2f _pos, sf::Vector2f _size, std::string _texture = "", sf::IntRect _textureRect = sf::IntRect(0, 0, 32, 32),bool _shouldColide = true);
	~Tile();
};

