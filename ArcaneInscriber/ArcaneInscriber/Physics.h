#pragma once
#include <SFML\Graphics.hpp>
class Physics
{
private:
	float mass;
	float friction;
	sf::Vector2f position;
	sf::Vector2f velocity;
public:
	bool onGround;
	Physics(float _mass, float _friction, sf::Vector2f _position, sf::Vector2f _velocity);
	float getMass();
	float getFriction();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void setMass(float _mass);
	void setFriction(float _friction);
	void setPosition(sf::Vector2f _position);
	void setVelocity(sf::Vector2f _velocity);
	void addVelocity(sf::Vector2f _velocity);
	void move(sf::Vector2f _position);
	void move(float X, float Y);
	virtual ~Physics();
};

