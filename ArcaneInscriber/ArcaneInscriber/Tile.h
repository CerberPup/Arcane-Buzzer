#pragma once
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
	Tile(sf::Vector2f _pos, sf::Vector2f _size);
	~Tile();
};

