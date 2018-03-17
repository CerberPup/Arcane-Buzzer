#pragma once
#include <SFML\Graphics.hpp>
class Engine
{
public:
	enum State{SPLASH,MAINMENU,GAME,EXIT};
	static State state;
	const unsigned short width;
	const unsigned short height;
	static sf::RenderWindow window;
	Engine(int w, int h);
	~Engine();
};

