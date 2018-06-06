#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Physics.h"
#include "Animable.h"
#include "Entity.h"
#include "HasLife.h"

class Enemy :public sf::Transformable, public sf::Drawable, public Animable, public Physics, public Entity, public HasLife
{
public:
	enum Direction {
		RIGHT, LEFT
	};
	bool canAnimate();
	int state;
	sf::Vector2f oldPosition;
	void Face(Direction d);
	void kaputt();
	virtual void Update();
	Enemy(sf::Vector2f position);
	void actualizePosition(sf::Vector2f pos);
	bool checkPosition(sf::Vector2f pos);
	Direction lastDir;
	int notMoving;
	~Enemy();

private:
	sf::Texture* texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

