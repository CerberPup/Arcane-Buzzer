#pragma once
#include "Animable.h"
#include "Engine.h"
#include "Logger.h"
#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include <SFML\Graphics.hpp>
#include <thread>
#include <Windows.h>
#include <list>
#include <algorithm>

//#define GRID
//#define NOCLIP
//#define COLBOX
//!Main class with game main loop.
class Game
{
private:
	//!Keeps current view.
	sf::View view;
	//!Determines if animation thread shoud keep running.
	bool doAnimate;
	//!Determines if physics thread shoud keep running.
	bool doPhysics;
	//!List of animable objects.
	std::list<Animable*> animationList;
	//!List of objects that move based on physics.
	std::list<Physics*> physicsList;
	//!List of objects that trigger collision.
	std::list<Physics*> colisionList;
	//!Player instance
	Player player;
	//!Used to determine elapsed time for physics calculation.
	sf::Clock clockphysic;
	//!Runs PhysicsLoop() method
	std::thread* physicLoop;
	//!Runs AnimationLoop() method
	std::thread* animationLoop;
	//!Calls method Engine::Physic() every 10ms
	void PhysicsLoop();
	//!Calls method update() every 100ms
	void AnimationLoop();
	//!Shows death splash screen
	void DeathSpash();
	//!Map instance
	Map map;
	//!Debug grid
#ifdef GRID
	//!Debug grid
	std::vector<sf::Vertex> grid;
	//!Debug grid
	void DrawGrid();
#endif // GRID
public:
	//!Initialize objects
	Game();
	//!Cleans memory and stops other threads
	~Game();
	//!Main loop
	void Run();
	
};

