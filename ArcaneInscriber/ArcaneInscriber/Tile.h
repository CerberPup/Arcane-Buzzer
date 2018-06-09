#pragma once
#include <string>
#include "Entity.h"
#include "Physics.h"
#include "Animable.h"
#include <SFML\Graphics.hpp>
//!Class for objects creating map
class Tile :
	public Entity,
	public sf::Transformable,
	public sf::Drawable,
	public Physics,
	public Animable
{
private:
	//!Draws tile sprite
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//!Is animable?
	bool animable;
	//!Should be drawn outside player vision?
	bool huge;
public:
	//!Creates new object.
	Tile(int _scale, sf::Vector2f _pos, sf::Vector2f _size, std::string _texture = "", sf::IntRect _textureRect = sf::IntRect(0, 0, 32, 32), bool _shouldColide = true, bool _shouldAnimate = false);
	//!Animable objects have to have function for updating sprite
	virtual void Update();
	//!Returns animable
	bool canAnimate();
	//!Should be drawn outside player vision
	bool drawAnyway();
	~Tile();
};

