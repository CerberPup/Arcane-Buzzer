#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Physics.h"
#include "animable.h"

class Player :public sf::Transformable , public sf::Drawable, public Animable,public Physics
{
private:
	sf::Texture* texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	bool onground;
	int animation;
	sf::Sprite sprite;
	enum Animation {
		LEFT, RIGHT, JUMP, IDDLE
	};
	virtual void Update();
	Player();
	~Player();
};

