#include "Game.h"
#include <vector>
#include <mutex>
#include "Logger.h"

Game::Game()
{
	clockphysic.restart();
	animationList.push_back(&player);
	physicsList.push_back(&player);
	doPhysics = true;
	doAnimate = true;
	physicLoop = new std::thread((&Game::PhysicsLoop), this);
	animationLoop = new std::thread((&Game::AnimationLoop), this);
}


Game::~Game()
{
	doAnimate = false;
	doPhysics = false;
	animationLoop->join();
	physicLoop->join();
	delete animationLoop;
	delete physicLoop;
}

void Game::PhysicsLoop()
{
	while (doPhysics) {
		float elapsed = clockphysic.getElapsedTime().asSeconds();
		clockphysic.restart();
		for (Physics* var : physicsList)
		{
			var->lock.lock();
			Engine::Physic(var, elapsed);
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
		//cout << "anim" << endl;
	}
}

void Game::Run()
{
	
	int posX = 0;
	while (Engine::state == Engine::State::GAME)
	{
		LOG(0, "Predkosc: ", player.getVelocity().x);
		//Vector2f mouse(Mouse::getPosition(*window));
		sf::Event event;

		while (Engine::window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed
				|| event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Escape) {
				Engine::state = Engine::State::EXIT;
				return;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.onGround = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (player.onGround) {
				player.animation = Player::JUMP;
				player.lock.lock();
				player.onGround = false;
				player.setVelocity(sf::Vector2f(player.getVelocity().x,-800));
				player.lock.unlock();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.Face(Player::Direction::LEFT);
			if (player.sprite.getPosition().x > 0) {
				if (player.onGround&&player.canAnimate())
				player.animation = Player::MOVE;
				player.lock.lock();
				player.addVelocity( sf::Vector2f(-50,0));
				player.lock.unlock();
			}
			else {
				player.sprite.setPosition(0, player.sprite.getPosition().y);
			}
			//Player goes Left/Player stops/Player slows down
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.Face(Player::Direction::RIGHT);
			if (player.sprite.getPosition().x < 1300) {
				player.lock.lock();
				player.addVelocity(sf::Vector2f(50, 0));
				player.lock.unlock();
				if (player.onGround&&player.canAnimate())
				player.animation = Player::MOVE;
			}
			else {
				player.sprite.setPosition(1300, player.sprite.getPosition().y);
			}
			/*if (posX < 5000)
			{
				posX += 5;
				map->Reposition(-1);
			}*/
		}
		//spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));
		/*if (player.sprite.getPosition().x > 520) {
		Sleep(100);
		GiveScript();
		if (Pyth("py", "multiply", "5", "4") == Pyth("script", "multiply", "5", "4")) {
		MessageBox(NULL, TEXT("Rozwi�za�e� poprawnie zadanie."), TEXT("Gratulacje"), NULL);
		}
		else {
		MessageBox(NULL, TEXT("Tym razem nie uda�o Ci si� rozwi�za� zadania. Pr�buj dalej."), TEXT("Ups..."), NULL);
		}
		*state = Engine::EXIT;

		}*/
		//cout << player.sprite.getPosition().x<<endl;

		//Player rotates 15

		Engine::window.clear(sf::Color(30,30,30));

		//Engine::window.draw(spriteBack);

		//map->Display(posX / 32);

		Engine::window.draw(player);
		//window->draw(wonsz);
		Engine::window.display();
	}
}
