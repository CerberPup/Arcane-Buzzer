#include "Player.h"


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

bool Player::canAnimate()
{
	if (animationcounter == 0)
		return true;
	return false;
}

void Player::Face(Direction d)
{
	if (lastDir != d) {
		sf::Vector2f Scale = sprite.getScale();
		Scale.x = Scale.x*-1;
		sprite.setScale(Scale);
		lastDir = d;
	}

}

void Player::Update()
{
	if (tookDamage) {
		damageCooldown--;
		if (damageCooldown > 0) {
			sprite.setColor(sf::Color(200 -  10* (6 - damageCooldown), 30, 30, 255));
		}
		else {
			sprite.setColor(sf::Color(255, 255, 255, 255));
			tookDamage = false;
		}
	}

	sf::IntRect tmp = sprite.getTextureRect();
	switch (animation)
	{
	case Player::Animation::IDDLE:
		break;
	case Player::Animation::MOVE:
	{
		if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
			animation = Player::Animation::IDDLE;
		}
		else {
			tmp.left += 32;
			animationcounter++;
		}
	}
	break;
	case Player::Animation::JUMP:
		if (animationcounter == 0)
			tmp.left = 4 * 32;
		if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
			animation = Player::Animation::IDDLE;
		}
		else {
			if (onGround||animationcounter<2){
			tmp.left += 32;
			animationcounter++;
			}
		}
		break;
	default:
		break;

	}
	sprite.setTextureRect(tmp);
}

Player::Player():Physics(1600,sf::Vector2f(16+32*2,1080-32*9),300,sf::Vector2f(0,0),sf::Vector2f(32,44), sf::Vector2f(-16, 20)),HasLife(3,6)
{
	onGround = true;
	animation = Player::Animation::IDDLE;
	sprite.setTexture(*Engine::getTexture("playerModels"));
	sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	sprite.setOrigin(16, 0);
	sprite.setScale(2, 2);
	lastDir = Direction::RIGHT;
}


Player::~Player()
{
}
