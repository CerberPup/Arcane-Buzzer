#include "Physics.h"

Physics::Physics(float _mass, float _friction, sf::Vector2f _position, sf::Vector2f _velocity):mass(_mass),friction(_friction),position(_position),velocity(_velocity)
{
}

float Physics::getMass()
{
	return mass;
}

float Physics::getFriction()
{
	return friction;
}

sf::Vector2f Physics::getPosition()
{
	return position;
}

sf::Vector2f Physics::getVelocity()
{
	return velocity;
}

void Physics::setMass(float _mass)
{
	mass = _mass;
}

void Physics::setFriction(float _friction)
{
	friction = _friction;
}

void Physics::setPosition(sf::Vector2f _position)
{
	position = _position;
}

void Physics::setVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}

void Physics::addVelocity(sf::Vector2f _velocity)
{
	velocity += _velocity;
}

void Physics::move(sf::Vector2f _position)
{
	position += _position;
}

void Physics::move(float X,float Y)
{
	position += sf::Vector2f(X,Y);
}

Physics::~Physics()
{
}
