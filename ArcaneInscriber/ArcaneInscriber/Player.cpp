#include "Player.h"


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Player::Update()
{

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
