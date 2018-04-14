#include "Engine.h"


std::shared_ptr<sf::Texture > Engine::getTexture(std::string Name)
{
	auto wynik = Tex.find(Name);
	if (wynik == Tex.end())
	{
		return nullptr;
	}
	else {
		return wynik->second;
	}
}

void Engine::setTexture(std::string Path, std::string Name)
{
	struct stat buffer;

	if (stat(Path.c_str(), &buffer) == 0) {
		//Logger::log(__FILE__, "","");
		LOG(0,"Plik Istnieje",Path,1);
		if (Tex.find(Name) == Tex.end()) 
		{
			sf::Texture* t = new sf::Texture;
			if (!t->loadFromFile(Path)) {
				throw std::runtime_error("Nie udalo sie zaladowac textury: " + Path);
			}
			Tex.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(Name, t));
		}
		else 
		{
			//LOG(0, "Tekstura istnieje", Name, 1);
		}
	}
	else {
		throw std::invalid_argument("Plik nie istnieje \""+Path+'\"');
	}
	return;
	
	
}
#define Gravity 2400
void Engine::Physic(Physics* obj,float& elapsed,const std::list<Physics*>& collision)
{
	sf::Vector2f position = obj->getPos();
	sf::Vector2f velocity = obj->getVelocity();

	velocity.y /= elapsed;//m/s^2
	velocity.y += Gravity;
	velocity.y *= elapsed;

	float halfScreenY = 1000;
	if (velocity.x > 1 || velocity.x < -1) {
		bool signBefore = std::signbit(velocity.x);
		velocity.x /= elapsed;
		velocity.x += obj->getFriction() * (velocity.x > 0 ? -1 : 1);
		velocity.x *= elapsed;
		if (signBefore != std::signbit(velocity.x))
			velocity.x = 0;
	}
	else {
		velocity.x = 0;
	}
	sf::Vector2f distance(velocity);
	distance.x *= elapsed;
	distance.y *= elapsed;
	if (position.y + distance.y > halfScreenY) {
		//sprite.setPosition(position.x, halfScreenY - 1);
		obj->onGround = true;
		velocity.y = 0;
		distance.y = halfScreenY - position.y;
	}

	obj->setVelocity(velocity);
	sf::Vector2f max(50, 50);
	sf::Vector2f dif;
	for (auto it = collision.begin(); it != collision.end(); it++)
	{
		if (obj != (*it)) {
			dif = dist(obj, (*it));
			min(max, dif);
		}
	}
	obj->move(abs(distance.x)<abs(max.x) ? distance.x : max.x, abs(distance.y)<abs(max.y) ? distance.y : max.y);
}

void Engine::min(sf::Vector2f& obj1, sf::Vector2f& obj2)
{
	if (abs(obj2.x) < abs(obj1.x))
		obj1.x = obj2.x;
	if (abs(obj2.y) < abs(obj1.y))
		obj1.y = obj2.y;
}

sf::Vector2f Engine::dist(Physics* obj1, Physics* obj2)
{
	sf::FloatRect obj1rect = obj1->getRect();
	sf::FloatRect obj2rect = obj2->getRect();
	sf::Vector2f velocity = obj1->getVelocity();
	sf::Vector2f dist(50,50);
	if (!((obj1rect.left + obj1rect.width)<obj2rect.left || obj1rect.left>obj2rect.left + obj2rect.width)) {
		if (velocity.y > 0) {
			if (obj1rect.top < obj2rect.top) {//obj1 powy¿ej obj2
				dist.y = obj2rect.top - obj1rect.top - obj1rect.height-0.5f;
				if (dist.y <= 0)
				{
					obj1->onGround = true;
					dist.y = 0;
					obj1->setVelocityY(0);
				}
			}
		}
		else {
			if (obj1rect.top > obj2rect.top) {//obj1 poni¿ej obj2
				dist.y = obj2rect.top + obj2rect.height - obj1rect.top+0.5f;
				if (dist.y >= 0)
				{
					dist.y = 0;
					obj1->setVelocityY(0);
				}
			}
		}
	}
	if (!((obj1rect.top + obj1rect.height) < obj2rect.top || obj1rect.top > obj2rect.top + obj2rect.height)) {
		if (velocity.x > 0) {
			if (obj1rect.left < obj2rect.left) {//obj1 po lewej obj2
				dist.x = obj2rect.left - obj1rect.left - obj1rect.width-0.5f;
				if (dist.x <= 0)
				{
					dist.x = 0;
					obj1->setVelocityX(0);
				}
			}
		}
		else {
			if (obj1rect.left > obj2rect.left) {//obj1 po prawej obj2
				dist.x = obj2rect.left + obj2rect.width - obj1rect.left+0.5f;
				if (dist.x >= 0)
				{
					dist.x = 0;
					obj1->setVelocityX(0);
				}
			}
		}
	}
	return dist;
}

void Engine::PhysicNoClip(Physics* obj, float& elapsed, const std::list<Physics*>& collision)
{
	
	sf::Vector2f position = obj->getPos();
	sf::Vector2f distance = obj->getVelocity();
	LOG(0, "Velocity", distance.x, distance.y);
	distance.x *= elapsed;
	distance.y *= elapsed;
	sf::Vector2f max(1000,1000);
	sf::Vector2f dif;
	for (auto it = collision.begin(); it != collision.end();it++)
	{
		if (obj != (*it)) {
			dif = dist(obj, (*it));
			min(max, dif);
		}
	}
	if (max.y > 0)
		obj->onGround = false;
	obj->move(abs(distance.x)<abs(max.x)? distance.x: max.x, abs(distance.y)<abs(max.y) ? distance.y : max.y);
}

Engine::Engine(int w, int h) :width(w), height(h)
{
	//window.create(sf::VideoMode(w, h), "Naked Archer King", sf::Style::Fullscreen);
	window.create(sf::VideoMode(w/2, h/2), "Naked Archer King");
	window.setFramerateLimit(60);
}


Engine::~Engine()
{
}

std::map<std::string, std::shared_ptr<sf::Texture >> Engine::Tex;
sf::RenderWindow Engine::window;
Engine::State Engine::state = State::SPLASH;