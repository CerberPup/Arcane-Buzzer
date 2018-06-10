#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Physics.h"
#include "Animable.h"
#include "Entity.h"
#include "HasLife.h"

//!Class representing an enemy 
class Enemy :public sf::Transformable, public sf::Drawable, public Animable, public Physics, public Entity, public HasLife
{
public:
	//!Enum for animation, representing the direction of enemy's movement
	enum Direction {
		RIGHT, LEFT
	};
	//!Determine if animation is over
	/*!
	\return true if animation is over.
	*/
	bool canAnimate();
	//!Determines state of the nenemy (alive, dying or dead)
	int state;
	//!Last known position of the enemy before updating
	sf::Vector2f oldPosition;
	//!Changes enemys orientation.
	/*!
	Mirrors enemys sprite by applying transformation.
	\param d Direction to set enemys orientation
	*/
	void Face(Direction d);
	//!Starts enemys dying animation and kills it
	void kaputt();
	//!Updates sprite to next frame.
	virtual void Update();
	Enemy(sf::Vector2f position);
	//!Actualizes the last know position
	void actualizePosition(sf::Vector2f pos);
	//!Checks if the last known position equals actual position
	bool checkPosition(sf::Vector2f pos);
	//!Previous frame looking direction
	Direction lastDir;
	//!Number of frames the enemy has stayed in the same position
	int notMoving;
	~Enemy();

private:
	//!Keeps texture loaded for future use.
	sf::Texture* texture;
	//!Generates sprite from internal data.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

