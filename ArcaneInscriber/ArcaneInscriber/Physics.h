#pragma once
#include <SFML\Graphics.hpp>
#include <mutex>

class Physics
{
private:
	float friction;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f offset;
	sf::Vector2f velocity;
	float maxXVelocity;
	void updateSprite();
public:
	enum SIDE
	{
		TOP,
		DOWN,
		LEFT,
		RIGHT
	};
	float getBorder(SIDE side);
	std::mutex lock;
	bool onGround;
	Physics(float _friction, sf::Vector2f _position,  float _maxXVelocity, sf::Vector2f _velocity,sf::Vector2f _size = sf::Vector2f(0,0), sf::Vector2f _offset = sf::Vector2f(0,0));
	Physics(sf::Vector2f _position, sf::Vector2f _size, sf::Vector2f _offset = sf::Vector2f(0, 0));
	sf::FloatRect getRect();
	sf::Vector2i getCoord();
	float getFriction();
	sf::Vector2f getPos();
	sf::Vector2f getVelocity();
	void setFriction(float _friction);
	void setPosition(sf::Vector2f _position);
	void setVelocity(sf::Vector2f _velocity);
	void setVelocityX(float x);
	void setVelocityY(float y);
	void addVelocity(sf::Vector2f _velocity);
	float getMaxXVelocity();
	void move(sf::Vector2f _position);
	void move(float X, float Y);
	void drawColisionBox();
	virtual ~Physics();
};

