#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Physics.h"
#include "Animable.h"
#include "Entity.h"
#include "HasLife.h"

//!Class representing player.
class Player :public sf::Transformable, public sf::Drawable, public Animable, public Physics, public Entity, public HasLife
{
public:
	/**Enum for animations.
	*Each value represents current player animation.
	*/
	enum Animation {
		MOVE, /**< Moving sideways */
		JUMP, /**< Jump */
		IDDLE  /**< Iddle */
	};
	/**Enum for directions.
	*Used to determine player direction.
	*/
	enum Direction {
		RIGHT, LEFT
	};
	//!Determine if animation is over
	/*!
	\return true if animation is over.
	*/
	bool canAnimate();
	//!Changes player orientation.
	/*!
		Mirrors player sprite by applying transformation.
		\param d Direction to set player orientation
	*/
	void Face(Direction d);
	//!Updates sprite to next frame.
	virtual void Update();
	//!Creates new player
	/*!
		Set his sprite, size, position, hp, damage cooldown and physics atributes 
	*/
	Player();
	~Player();

private:
	//!Keeps texture loaded for future use.
	sf::Texture* texture;
	//!Previous frame looking direction
	Direction lastDir;
	//!Generates sprite from internal data.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

