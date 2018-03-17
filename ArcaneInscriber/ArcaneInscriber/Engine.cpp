#include "Engine.h"



Engine::Engine(int w, int h) :width(w), height(h)
{
	window.create(sf::VideoMode(w, h), "Gra",sf::Style::Fullscreen);
	window.setFramerateLimit(60);
}


Engine::~Engine()
{
}

sf::RenderWindow Engine::window;
Engine::State Engine::state = State::SPLASH;