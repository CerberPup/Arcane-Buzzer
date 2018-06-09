#pragma once
#include <SFML\Graphics.hpp>
#include <mutex>

//!Class for inheritance of objects with physics properties.
class Physics
{
private:
	//!Determine friction with floor.
	float friction;
	//!Is collidable?
	bool shouldColide;
	//!Position of object.
	sf::Vector2f position;
	//!Size of object.
	sf::Vector2f size;
	//!offset of collision box.
	sf::Vector2f offset;
	//!Velocity.
	sf::Vector2f velocity;
	//!Maximum object velocity.
	float maxXVelocity;
	//!Updates sprite position to position variable value.
	void updateSprite();
public:
	//!Used to determine object side position.
	enum SIDE
	{
		TOP,
		DOWN,
		LEFT,
		RIGHT
	};
	/*!Calculate edge position.
	\return Position
	\argument side = requested side
	*/
	float getBorder(SIDE side);
	//!Used to lock velocity modifications.
	std::mutex lock;
	//!Can jump?
	bool onGround;
	Physics(float _friction, sf::Vector2f _position,  float _maxXVelocity, sf::Vector2f _velocity,sf::Vector2f _size = sf::Vector2f(0,0), sf::Vector2f _offset = sf::Vector2f(0,0));
	Physics(sf::Vector2f _position, sf::Vector2f _size, bool _shouldColide = true, sf::Vector2f _offset = sf::Vector2f(0, 0));
	Physics(sf::Vector2f _position, sf::Vector2f _size, sf::Vector2f _offset = sf::Vector2f(0, 0));
	//!Returns object rectangle.
	sf::FloatRect getRect();
	//!Returns object position.
	sf::Vector2i getCoord();
	//!Returns object friction.
	float getFriction();
	//!Returns object position.
	sf::Vector2f getPos();
	//!Returns object velocity.
	sf::Vector2f getVelocity();
	//!Sets object friction.
	void setFriction(float _friction);
	//!Sets object position.
	void setPosition(sf::Vector2f _position);
	//!Sets object velocity.
	void setVelocity(sf::Vector2f _velocity);
	//!Sets object horizontal velocity.
	void setVelocityX(float x);
	//!Sets object vertical velocity.
	void setVelocityY(float y);
	//!Adds velocity to object, capped at maxXVelocity value.
	void addVelocity(sf::Vector2f _velocity);
	//!Returns if object might colide.
	bool getColisionPossibility();
	//!Returns max horizontal velocity.
	float getMaxXVelocity();
	//!Move object to position.
	void move(sf::Vector2f _position);
	//!Move object to position.
	void move(float X, float Y);
	//!Draws collision box around object.
	void drawColisionBox();

	virtual ~Physics();
};

