#include "Tile.h"
#include "Engine.h"

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Tile::Tile(int _scale, sf::Vector2f _pos, sf::Vector2f _size, std::string _texture, sf::IntRect _textureRect, bool _shouldColide, bool _shouldAnimate) :Physics(_pos, _size, _shouldColide)
{
	if (_texture != "") {
		sprite.setTexture(*Engine::getTexture(_texture));
		sprite.setTextureRect(_textureRect);
		//sprite.setOrigin(_pos.x, _pos.y);
		sprite.setPosition(_pos.x, _pos.y);
		sprite.setScale(_scale + 0.0015, _scale + 0.0015);
		animable = _shouldAnimate;
		animationcounter = 0;
		if (_scale > 3)
			huge = true;
		else
			huge = false;
	}
}

bool Tile::drawAnyway()
{
	if (huge)
		return true;
	return false;
}

void Tile::Update()
{
	sf::IntRect tmp = sprite.getTextureRect();
	if (animationcounter > 12)
	{
		tmp.left = 224;
		animationcounter = 0;
	}
	else
	{
		if(animationcounter == 6)
			tmp.left += 16;
		animationcounter++;
	}
	sprite.setTextureRect(tmp);
}

bool Tile::canAnimate()
{
	if (animable == true)
		return true;
	return false;
}

Tile::~Tile()
{
}
