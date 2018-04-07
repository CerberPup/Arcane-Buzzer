#pragma once
#include <SFML\Graphics.hpp>
#include <mutex>
class Physics
{
private:
	float friction;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float maxXVelocity;
public:
	std::mutex lock;
	bool onGround;
	Physics(float _friction, sf::Vector2f _position, sf::Vector2f _velocity, float _maxXVelocity);
	float getFriction();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void setFriction(float _friction);
	void setPosition(sf::Vector2f _position);
	void setVelocity(sf::Vector2f _velocity);
	void addVelocity(sf::Vector2f _velocity);
	float getMaxXVelocity();
	void move(sf::Vector2f _position);
	void move(float X, float Y);
	virtual ~Physics();
};

