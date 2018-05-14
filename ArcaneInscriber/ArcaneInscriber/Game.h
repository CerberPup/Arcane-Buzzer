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

//#define GRID
//#define NOCLIP
//#define COLBOX

class Game
{
private:
	sf::View view;
	bool doAnimate, doPhysics;
	std::list<Animable*> animationList;
	std::list<Physics*> physicsList;
	std::list<Physics*> colisionList;
	Player player;
	sf::Clock clockphysic;
	std::thread* physicLoop;
	std::thread* animationLoop;
	void PhysicsLoop();
	void AnimationLoop();
	void DeathSpash();
	Map map;
#ifdef GRID
	std::vector<sf::Vertex> grid;
	void DrawGrid();
#endif // GRID
public:
	
	Game();
	~Game();
	void Run();
	
};

