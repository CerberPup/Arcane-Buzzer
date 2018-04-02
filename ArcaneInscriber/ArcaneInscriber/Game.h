#pragma once
#include "Engine.h"
#include "Logger.h"
#include "Player.h"
#include "Animable.h"
#include <SFML\Graphics.hpp>
#include <thread>
#include <Windows.h>
#include <list>
class Game
{
private:
	bool doAnimate, doPhysics;
	std::list<Animable*> animable;
	std::list<Physics*> physics;
	Player player;
	sf::Clock clockphysic;
	std::thread* physicLoop;
	std::thread* animationLoop;
	void PhysicsLoop();
	void AnimationLoop();
public:
	
	Game();
	~Game();
	void Run();
	
};

