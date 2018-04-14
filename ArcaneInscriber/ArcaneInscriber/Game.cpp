#include "Game.h"
#include <vector>
#include <mutex>
#include <memory>
#include "Tile.h"
#include "Logger.h"
#pragma warning( disable : 4244) // Ostrzezenie o konwersji unsigned -> float
Game::Game()
{
	clockphysic.restart();
	animationList.push_back(&player);
	physicsList.push_back(&player);
	colisionList.push_back(dynamic_cast<Physics*>(new Tile(sf::Vector2f(150, 1000), sf::Vector2f(32, 32))));
	colisionList.push_back(dynamic_cast<Physics*>(new Tile(sf::Vector2f(150+128, 1000-128), sf::Vector2f(32, 32))));
	doPhysics = true;
	doAnimate = true;
	physicLoop = new std::thread((&Game::PhysicsLoop), this);
	animationLoop = new std::thread((&Game::AnimationLoop), this);
	view = sf::View(player.getPos() , sf::Vector2f(Engine::window.getSize()));
	Engine::window.setView(view);
}

Game::~Game()
{
	Engine::window.setMouseCursorVisible(true);
	doAnimate = false;
	doPhysics = false;
	animationLoop->join();
	physicLoop->join();
	delete animationLoop;
	delete physicLoop;
	while (!colisionList.empty()) delete colisionList.front(), colisionList.pop_front();
	Engine::window.setView(Engine::window.getDefaultView());
}

//#define NOCLIP
#define COLBOX

void Game::PhysicsLoop()
{
	while (doPhysics) {
		view.setCenter(player.getPos());
		Engine::window.setView(view);
		float elapsed = clockphysic.getElapsedTime().asSeconds();
		clockphysic.restart();
		for (Physics* var : physicsList)
		{
			var->lock.lock();
#ifndef NOCLIP
			Engine::Physic(var, elapsed, colisionList);
#else
			Engine::PhysicNoClip(var, elapsed,colisionList);
#endif // !NOCLIP
			var->lock.unlock();
		}
		Sleep(10);
	}
}

void Game::AnimationLoop()
{
	while (doAnimate) {
		for (Animable* var : animationList)
		{
			var->Update();
		}
		Sleep(100);
	}
}

void Game::Run()
{
	while (Engine::state == Engine::State::GAME)
	{
		Engine::window.setMouseCursorGrabbed(false);
		Engine::window.setMouseCursorVisible(false);
		//Vector2f mouse(Mouse::getPosition(*window));
		sf::Event event;
		bool focus = true;
		while (Engine::window.pollEvent(event))
		{
			if (event.type == sf::Event::LostFocus) {
				bool focus = false;
				while (Engine::window.pollEvent(event) || !focus)
				{
					if (event.type == sf::Event::GainedFocus) {
						focus = true;
					}
					Sleep(20);
				}
			}
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				view.setSize(event.size.width, event.size.height);
				Engine::window.setView(view);
			}

			if (event.type == sf::Event::Closed
				|| event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Escape) {
				Engine::state = Engine::State::EXIT;
				return;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			view.zoom(0.99);
			Engine::window.setView(view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
			view.zoom(1.01);
			Engine::window.setView(view);
		}

#ifdef NOCLIP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			player.setVelocity(sf::Vector2f(0, 0));
		}
#endif
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
#ifdef NOCLIP
			player.addVelocity(sf::Vector2f(0, +10));
#endif
			player.onGround = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
#ifndef NOCLIP
			if (player.onGround) {
				player.animation = Player::JUMP;
				player.lock.lock();
				player.onGround = false;
				player.setVelocity(sf::Vector2f(player.getVelocity().x,-800));
				player.lock.unlock();
			}
#else
				player.animation = Player::JUMP;
				player.lock.lock();
				player.addVelocity(sf::Vector2f(0, -10));
				player.lock.unlock();
#endif
				
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.Face(Player::Direction::LEFT);
			if (player.onGround&&player.canAnimate())
				player.animation = Player::MOVE;
			player.lock.lock();
#ifndef NOCLIP
			player.addVelocity( sf::Vector2f(-50,0));
#else
			player.addVelocity(sf::Vector2f(-10, 0));
#endif
			player.lock.unlock();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.Face(Player::Direction::RIGHT);
			if (player.sprite.getPosition().x < 1300) {
				player.lock.lock();
#ifndef NOCLIP
				player.addVelocity(sf::Vector2f(50, 0));
#else
				player.addVelocity(sf::Vector2f(+10, 0));
#endif
				player.lock.unlock();
				if (player.onGround&&player.canAnimate())
				player.animation = Player::MOVE;
			}
			else {
				player.sprite.setPosition(1300, player.sprite.getPosition().y);
			}
		}

		Engine::window.clear(sf::Color(30,30,30));
		sf::Vertex outline[] =
		{
			sf::Vertex(sf::Vector2f(0,0),sf::Color(255,0,0)),
			sf::Vertex(sf::Vector2f(1920,0),sf::Color(0,255,0)),
			sf::Vertex(sf::Vector2f(1920,1080),sf::Color(0,0,255)),
			sf::Vertex(sf::Vector2f(0,1080),sf::Color(0,0,0))

		};
		Engine::window.draw(outline, 4, sf::TrianglesFan);
#ifdef GRID
		DrawGrid();
#endif // GRID
		Engine::window.draw(player);
#ifdef COLBOX
		sf::Vector2i coord = player.getCoord();
		//LOG(0, "Pozycja", coord.x, coord.y,"Fizycznie :",player.getPos().x,player.getPos().y);
		for (Physics* var : physicsList)
		{
			var->drawColisionBox();
		}
		(*colisionList.begin())->drawColisionBox();
		(*++colisionList.begin())->drawColisionBox();
#endif
		Engine::window.display();
	}
}
#ifdef GRID
void Game::DrawGrid() {
	if (grid.size() == 0) {
		sf::Vector2u size(1920,1080);
		for (unsigned int i = 0; i < size.x; i += 32) {
			grid.push_back(sf::Vertex(sf::Vector2f(size.x - i, 0),sf::Color(0,255,0,0)));
			grid.push_back(sf::Vertex(sf::Vector2f(size.x - i, size.y), sf::Color(255, 0, 0)));
		}
		for (unsigned int i = 0; i < size.y; i += 32) {
			grid.push_back(sf::Vertex(sf::Vector2f(0, size.y - i), sf::Color(0, 0, 255,0)));
			grid.push_back(sf::Vertex(sf::Vector2f(size.x, size.y- i), sf::Color(255, 0, 0)));
		}
	}
	Engine::window.draw(&grid[0],grid.size(),sf::Lines);

}
#endif // GRID
