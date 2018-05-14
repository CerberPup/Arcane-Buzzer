#pragma once
#include <string>
#include "Entity.h"
#include "Physics.h"
#include "Animable.h"
#include <SFML\Graphics.hpp>
class Tile :
	public Entity,
	public sf::Transformable,
	public sf::Drawable,
	public Physics,
	public Animable
{
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool animable;
	bool huge;
public:
	Tile();
	Tile(int _scale, sf::Vector2f _pos, sf::Vector2f _size, std::string _texture = "", sf::IntRect _textureRect = sf::IntRect(0, 0, 32, 32), bool _shouldColide = true, bool _shouldAnimate = false);
	virtual void Update();
	bool canAnimate();
	bool drawAnyway();
	~Tile();
};

