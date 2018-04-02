#include "Player.h"


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Player::Update()
{
	sf::IntRect tmp = sprite.getTextureRect();
	switch (animation)
	{
	case Player::Animation::IDDLE:
		offset = 0;
		break;
	case Player::Animation::RIGHT:
	{
		offset = 0;
		sf::Vector2f tmp2 = sprite.getScale();
		if (tmp2.x < 0)
			tmp2.x = tmp2.x*-1;
		sprite.setScale(tmp2);
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
	case Player::Animation::LEFT:
	{
		offset = 0;
		sf::Vector2f tmp2 = sprite.getScale();
		if (tmp2.x > 0)
			tmp2.x = tmp2.x*-1;
		sprite.setScale(tmp2);
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
			if (onground||animationcounter<2){
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

Player::Player()
{
	animation = 0;
	sprite.setTexture(*Engine::getTexture("playerModels"));
	sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	sprite.move(263, 800);
	sprite.setOrigin(16, 0);
	sprite.setScale(2, 2);
	//velocity = Vector2f(0, 0);
	onground = true;
}


Player::~Player()
{
}
