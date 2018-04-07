#include "Physics.h"
#include "Logger.h"
Physics::Physics(float _friction, sf::Vector2f _position, sf::Vector2f _velocity, float _maxXVelocity):friction(_friction),position(_position),velocity(_velocity),maxXVelocity(_maxXVelocity)
{
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
	if (_velocity.x < 0) {
		float max = velocity.x + maxXVelocity;
		if (max<-_velocity.x)
			_velocity.x = -max;
	}
	else if(_velocity.x > 0){
		float max = maxXVelocity - velocity.x;
		if (max < _velocity.x)
			_velocity.x = max;
	}
	velocity += _velocity;
}

float Physics::getMaxXVelocity()
{
	return maxXVelocity;
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
