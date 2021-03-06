#include "Game.h"
#include <vector>
#include <mutex>
#include <memory>
#include "Tile.h"
#include "Logger.h"
#include <iostream>
#pragma warning( disable : 4244) // Ostrzezenie o konwersji unsigned -> float
Game::Game()
{
	clockphysic.restart();
	animationList.push_back(&player);
	physicsList.push_back(&player);
	for (Tile* tile : map.mapTiles)
	{
		if(tile->getColisionPossibility())
			colisionList.push_back(tile);
		if (tile->canAnimate())
			animationList.push_back(tile);
	}
	for (Enemy* enemy : map.enemies)
	{
		//colisionList.push_back(enemy);
		animationList.push_back(enemy);
		physicsList.push_back(enemy);
	}
	doPhysics = true;
	doAnimate = true;
	physicLoop = new std::thread((&Game::PhysicsLoop), this);
	animationLoop = new std::thread((&Game::AnimationLoop), this);
	view = sf::View(player.getPos() , sf::Vector2f(Engine::window.getSize()));
	Engine::window.setView(view);
	view.zoom(0.99);
	Engine::window.setView(view);
	view.zoom(1.01);
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

void Game::DeathSpash() {
	sf::Texture ScreenCopy;
	sf::Vector2u size = Engine::window.getSize();
	ScreenCopy.create(size.x, size.y);
	ScreenCopy.update(Engine::window);
	sf::Sprite ScreenCopyS(ScreenCopy);
	ScreenCopyS.setColor(sf::Color(255,255,255,120));
	sf::Vector2f f = view.getSize();
	ScreenCopyS.setPosition(view.getCenter().x-f.x/2, view.getCenter().y - f.y / 2);
	sf::Font font;
	if (!font.loadFromFile("Resources/Pentagram.ttf")) {
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}
	sf::Text title("YOU DIED", font, 40);
	title.setStyle(sf::Text::Bold);
	title.setPosition(view.getCenter().x - title.getGlobalBounds().width/2, view.getCenter().y-40);
	sf::Color c(180, 30, 30, 0);
	title.setFillColor(c);
	for (int i = 0; i < 46; i++)
	{
		Engine::window.clear(sf::Color(0, 0, 0, 255));
		Engine::window.draw(ScreenCopyS);
		Engine::window.draw(title);
		Engine::window.display();
		c.a += 3;
		Sleep(30);
		title.setFillColor(c);
	}

}

bool sort(const Enemy* obj1, const Enemy* obj2) 
{ 
	return obj1->HP > obj2->HP; 
}

void Game::Run()
{
	while (Engine::state == Engine::State::GAME)
	{
		if (player.HP <= 0) {
			DeathSpash();
			Engine::state = Engine::State::MAINMENU;
			continue;
		}
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			player.TakeDamage();
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
			std::cout << "\n" << Game::view.getCenter().x << ", " << Game::view.getCenter().y << "\t" << player.getBorder(Physics::SIDE::DOWN) << ", " << map.enemies.at(0)->getBorder(Physics::SIDE::TOP);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
#ifndef NOCLIP
			if (player.onGround) {
				player.animation = Player::JUMP;
				player.lock.lock();
				player.onGround = false;
				player.setVelocity(sf::Vector2f(player.getVelocity().x, -800));
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
			player.addVelocity(sf::Vector2f(-50, 0));
#else
			player.addVelocity(sf::Vector2f(-10, 0));
#endif
			player.lock.unlock();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.Face(Player::Direction::RIGHT);
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

		Engine::window.clear(sf::Color(30,30,30));
#ifdef GRID
		DrawGrid();
#endif // GRID
		map.Display(view.getCenter(), view.getSize());
		for (Enemy* enemy : map.enemies)
		{
			if (enemy->state == 2)
			{
				if (enemy->getRect().intersects(player.getRect()))
				{
					if (enemy->getBorder(Physics::SIDE::TOP) > (player.getBorder(Physics::SIDE::DOWN) + 5.5))
					{
						enemy->TakeDamage();
						player.animation = Player::JUMP;
						player.lock.lock();
						player.onGround = false;
						player.setVelocity(sf::Vector2f(player.getVelocity().x, -500));
						player.lock.unlock();
						if (enemy->HP <= 0)
						{
							std::sort(map.enemies.begin(), map.enemies.end(), sort);
							if (enemy->state == 2)
								enemy->kaputt();
						}
					}
					else
						player.TakeDamage();
				}
				if (enemy->lastDir == Enemy::Direction::RIGHT)
					enemy->setVelocityX(70);
				else
					enemy->setVelocityX(-70);
				if (enemy->checkPosition(enemy->getPos()))
				{
					if (enemy->lastDir == Enemy::Direction::RIGHT)
						enemy->Face(Enemy::Direction::LEFT);
					else
						enemy->Face(Enemy::Direction::RIGHT);
				}
				else
					enemy->actualizePosition(enemy->getPos());
			}
			Engine::window.draw(*enemy);
		}
		Engine::window.draw(player);
#ifdef COLBOX

		LOG(0, "Predkosc", player.getVelocity().y);
		for (Physics* var : physicsList)
		{
			var->drawColisionBox();
		}
		for (auto obj : colisionList)
		{
			obj->drawColisionBox();
		}
#endif
		Engine::window.display();
	}
}
#ifdef GRID
void Game::DrawGrid() {
	if (grid.size() == 0) {
		sf::Vector2u size(1920,1080);
		for (unsigned int i = 0; i < size.x; i += 32) {
			grid.push_back(sf::Vertex(sf::Vector2f(size.x - i, 0),sf::Color(0,128,0)));
			grid.push_back(sf::Vertex(sf::Vector2f(size.x - i, size.y), sf::Color(128, 0, 0)));
		}
		for (unsigned int i = 0; i < size.y; i += 32) {
			grid.push_back(sf::Vertex(sf::Vector2f(0, size.y - i), sf::Color(0, 128, 0)));
			grid.push_back(sf::Vertex(sf::Vector2f(size.x, size.y- i), sf::Color(128, 0, 0)));
		}
	}
	Engine::window.draw(&grid[0],grid.size(),sf::Lines);

}
#endif // GRID
