#pragma once

#include <memory>
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <list>
#include <sys\stat.h>
#include "Physics.h"
#include "Logger.h"
#include "Entity.h"


class Engine
{
private:
	static std::map<std::string, std::shared_ptr<sf::Texture>> Tex;
	static sf::Vector2f dist(Physics * obj1, Physics * obj2);
	static void min(sf::Vector2f & obj1, sf::Vector2f & obj2);
public:
	enum State { SPLASH, MAINMENU, GAME, EXIT };
	static State state;
	const unsigned short width;
	const unsigned short height;
	static std::shared_ptr<sf::Texture> getTexture(std::string Name);
	static void setTexture(std::string Path, std::string Name);
	static void Physic(Physics* obj, float& elapsed, const std::list<Physics*>& = {});
	
	static void PhysicNoClip(Physics * obj, float & elapsed, const std::list<Physics*>& = {});
	//Path,Name
	static sf::RenderWindow window;
	Engine(int w, int h);
	~Engine();
};