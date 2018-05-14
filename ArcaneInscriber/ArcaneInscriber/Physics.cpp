#include "Physics.h"
#include "Engine.h"
#include <cmath>

Physics::Physics(float _friction, sf::Vector2f _position, float _maxXVelocity, sf::Vector2f _velocity, sf::Vector2f _size, sf::Vector2f _offset):friction(_friction),position(_position),velocity(_velocity),maxXVelocity(_maxXVelocity),size(_size),offset(_offset)
{
}

Physics::Physics(sf::Vector2f _position, sf::Vector2f _size, bool _shouldColide, sf::Vector2f _offset) : position(_position), size(_size), offset(_offset),shouldColide(_shouldColide)
{
	friction = 0;
	velocity = sf::Vector2f(0, 0);
	maxXVelocity = 300;
}

Physics::Physics(sf::Vector2f _position, sf::Vector2f _size, sf::Vector2f _offset):position(_position),size(_size),offset(_offset)
{
	friction = 0;
	velocity = sf::Vector2f(0,0);
	maxXVelocity = 300;
}

sf::FloatRect Physics::getRect() {
	return sf::FloatRect(position + offset, size);
}

sf::Vector2i Physics::getCoord() 
{
	int y = Engine::window.getSize().y - position.y - size.y-offset.y;
	return sf::Vector2i(std::floor((position.x+offset.x)/32), std::floor(y / 32));
}

float Physics::getFriction()
{
	return friction;
}

sf::Vector2f Physics::getPos()
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

void Physics::setVelocityX(float x)
{
	velocity.x = x;
}

void Physics::setVelocityY(float y)
{
	velocity.y = y;
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

bool Physics::getColisionPossibility()
{
	return shouldColide;
}

float Physics::getMaxXVelocity()
{
	return maxXVelocity;
}

void Physics::updateSprite() {
	if (Entity* ent = dynamic_cast<Entity*>(this))
	{
		ent->sprite.setPosition(position);
	}
}

float Physics::getBorder(SIDE side)
{
	switch (side)
	{
	case Physics::TOP:
		return position.y;
		break;
	case Physics::DOWN:
		return position.y + size.y;
		break;
	case Physics::LEFT:
		return position.x;
		break;
	case Physics::RIGHT:
		return position.x + size.x;
		break;
	default:
		return 0;
		break;
	}
}

void Physics::move(sf::Vector2f _position)
{
	position += _position;
	updateSprite();
}

void Physics::move(float X,float Y)
{
	position += sf::Vector2f(X,Y);
	updateSprite();
}

void Physics::drawColisionBox()
{
	sf::Vertex outline[] =
	{
		sf::Vertex(position+offset),
		sf::Vertex(sf::Vector2f(position.x + size.x,position.y) + offset),
		sf::Vertex(position + size + offset),
		sf::Vertex(sf::Vector2f(position.x, position.y + size.y) + offset),
		sf::Vertex(position + offset)
	};
	Engine::window.draw(outline, 5, sf::LinesStrip);
}

Physics::~Physics()
{
}
