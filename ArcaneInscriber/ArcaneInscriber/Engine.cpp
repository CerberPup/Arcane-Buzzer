#include "Engine.h"
#include "Logger.h"
#include "Entity.h"


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
void Engine::Physic(Physics* obj,float& elapsed)
{
	if (Entity* ent = dynamic_cast<Entity*>(obj))
	{
		sf::Vector2f position = obj->getPosition();
		sf::Vector2f velocity = obj->getVelocity();
		if (!obj->onGround) {
			velocity.y /= elapsed;//m/s^2
			velocity.y += Gravity;
			velocity.y *= elapsed;
		}
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
		obj->move(distance);
		ent->sprite.setPosition(obj->getPosition());
	}
}

Engine::Engine(int w, int h) :width(w), height(h)
{
	window.create(sf::VideoMode(w, h), "Gra",sf::Style::Fullscreen);
	window.setFramerateLimit(60);
}


Engine::~Engine()
{
}

std::map<std::string, std::shared_ptr<sf::Texture >> Engine::Tex;
sf::RenderWindow Engine::window;
Engine::State Engine::state = State::SPLASH;