#pragma once
#ifndef Engine_H
#define Engine_H

#include <memory>
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <list>
#include <sys\stat.h>
#include "Physics.h"
#include "Logger.h"
#include "Entity.h"

//!Class providing global functionality
class Engine
{
private:
	//!Keeps loaded textures indexed by name.
	static std::map<std::string, std::shared_ptr<sf::Texture>> Tex;
	//!Calculate distance between 2 physics objects.
	static sf::Vector2f dist(Physics * obj1, Physics * obj2);
	/*!Finds minimal distance
	\param Max Current max distance, this object is changed to minimal x,y values of ToCompare
	\param ToCompare used to determine Max
	*/
	static void min(sf::Vector2f & Max, sf::Vector2f & ToCompare);
public:
	//!Current game state
	enum State { 
		SPLASH, /**< Start spalsh screen */
		MAINMENU,/**< Main menu */
		GAME,/**< Main game loop */
		EXIT /**< Game should close */
	};
	//!Current game state
	static State state;
	//!Window width
	const unsigned short width;
	//!Window height
	const unsigned short height;
	//!returns texture from name
	static std::shared_ptr<sf::Texture> getTexture(std::string Name);
	//!Loads texture to program memmory.
	static void setTexture(std::string Path, std::string Name);
	//!Determine object position based on elapsed time and collidable environment
	static void Physic(Physics* obj, float& elapsed, const std::list<Physics*>& = {});
	//!Determine object position based on elapsed time and collidable environment NO GRAVITY
	static void PhysicNoClip(Physics * obj, float & elapsed, const std::list<Physics*>& = {});
	//!Current window
	static sf::RenderWindow window;
	//!Creates window
	Engine(int w, int h);
	//!Makes game fullscreen
	static void toggleFullScreen(bool full);
	//!Makes window borderless
	static void setStyle(sf::Uint32 style);
	~Engine();
};

#endif // Engine_H