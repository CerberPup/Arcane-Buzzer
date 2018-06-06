#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position) :Physics(1600, position, 300, sf::Vector2f(0, 0), sf::Vector2f(22, 22), sf::Vector2f(-11, 0)), HasLife(2, 2)
{
	onGround = true;
	sprite.setTexture(*Engine::getTexture("slimes"));
	sprite.setTextureRect(sf::IntRect(10, 404, 14, 12));
	sprite.setOrigin(7, 0);
	sprite.setScale(2, 2);
	lastDir = Direction::LEFT;
	oldPosition = position;
	notMoving = 0;
	state = 2;
}

bool Enemy::canAnimate()
{
	if (animationcounter == 0)
		return true;
	return false;
}

void Enemy::Face(Direction d)
{
	if (lastDir != d) {
		sf::Vector2f Scale = sprite.getScale();
		Scale.x = Scale.x*-1;
		sprite.setScale(Scale);
		lastDir = d;
	}

}

void Enemy::actualizePosition(sf::Vector2f pos)
{
	oldPosition = pos;
}

bool Enemy::checkPosition(sf::Vector2f pos)
{
	if (oldPosition == pos)
		notMoving++;
	else
	{
		notMoving = 0;
		return false;
	}
	if (notMoving >= 5)
	{
		notMoving = 0;
		return true;
	}
	return false;
}

void Enemy::kaputt() // godzina 3:45AM, to nie bêdzie dzia³aæ :*
{
	sprite.setTextureRect(sf::IntRect(10, 470, 14, 12));
	sprite.setOrigin(7, 0);
	sprite.setScale(2, 2);
	animationcounter = 0;
	state = 1;
}

void Enemy::Update()
{
	if (tookDamage) {
		damageCooldown--;
		if (damageCooldown > 0) {
			sprite.setColor(sf::Color(200 - 10 * (6 - damageCooldown), 30, 30, 255));
		}
		else {
			sprite.setColor(sf::Color(255, 255, 255, 255));
			tookDamage = false;
		}
	}
	sf::IntRect tmp = sprite.getTextureRect();
	if (state == 2)
	{
		if (animationcounter == 9)
		{
			tmp.left = 10;
			animationcounter = 0;
		}
		else
		{
			tmp.left += 32;
			animationcounter++;
		}
		switch (animationcounter)
		{
		case 0:
			tmp.top = 405;
			break;
		case 1:
			tmp.top = 405;
			break;
		case 2:
			tmp.top = 403;
			break;
		case 3:
			tmp.top = 401;
			break;
		case 4:
			tmp.top = 400;
			break;
		case 5:
			tmp.top = 402;
			break;
		case 6:
			tmp.top = 403;
			break;
		case 7:
			tmp.top = 407;
			break;
		case 8:
			tmp.top = 408;
			break;
		case 9:
			tmp.top = 406;
			break;
		default:
			break;
		}
	}
	if (state == 1)
	{
		tmp.left += 64;
		animationcounter += 2;
		if (animationcounter >= 10 )
			state = 0;
	}
	sprite.setTextureRect(tmp);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Enemy::~Enemy()
{
}