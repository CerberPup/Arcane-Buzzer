#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Physics.h"
#include "Animable.h"
#include "Entity.h"

class Player :public sf::Transformable , public sf::Drawable, public Animable,public Physics,public Entity
{
public:
	enum Animation {
		MOVE, JUMP, IDDLE
	};
	enum Direction {
		RIGHT, LEFT
	};
	bool canAnimate();
	void Face(Direction d);
	virtual void Update();
	Player();
	~Player();

private:
	sf::Texture* texture;
	Direction lastDir;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

