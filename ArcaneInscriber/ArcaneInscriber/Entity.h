#pragma once
#include <SFML\Graphics.hpp>
//!Class for inheritance of objects with sprites
class Entity
{
public:
	//!Keeps sprite
	sf::Sprite sprite;
	Entity();
	~Entity();
};

