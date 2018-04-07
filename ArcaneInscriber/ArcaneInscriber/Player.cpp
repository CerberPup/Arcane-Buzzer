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

Player::Player():Physics(1200,sf::Vector2f(263,1000),sf::Vector2f(0,0),300)
{
	onGround = true;
	animation = Player::Animation::IDDLE;
	sprite.setTexture(*Engine::getTexture("playerModels"));
	sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	sprite.move(263, 1000);
	sprite.setOrigin(16, 0);
	sprite.setScale(2, 2);
	lastDir = Direction::RIGHT;
}


Player::~Player()
{
}
