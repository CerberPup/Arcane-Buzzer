#include "Game.h"
#include <vector>

Game::Game()
{
	clockphysic.restart();
	animable.push_back(&player);
	physics.push_back(&player);
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
		for (Physics* var : physics)
		{
			Engine::Physic(var, elapsed);
		}
		//player.physic(elapsed.asSeconds());
		Sleep(10);
	}
}

void Game::AnimationLoop()
{
	while (doAnimate) {
		for (Animable* var : animable)
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
			player.onground = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (player.onground) {
				player.onground = false;
				player.animation = Player::JUMP;
				//player.velocity.y = -600;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (player.sprite.getPosition().x > 0) {
				if (player.onground)
				player.animation = Player::LEFT;
				/*if (player.velocity.x > -200)
				player.velocity.x -= 50;*/
				if (posX > 0)
				{
					posX -= 5;
					//map->Reposition(1);
				}
			}
			else {
				player.sprite.setPosition(0, player.sprite.getPosition().y);
			}
			//Player goes Left/Player stops/Player slows down
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (player.sprite.getPosition().x < 1300) {
				/*if (player.velocity.x < 200)
				player.velocity.x += 50;*/
				if (player.onground)
				player.animation = Player::RIGHT;
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
		MessageBox(NULL, TEXT("Rozwi¹za³eœ poprawnie zadanie."), TEXT("Gratulacje"), NULL);
		}
		else {
		MessageBox(NULL, TEXT("Tym razem nie uda³o Ci siê rozwi¹zaæ zadania. Próbuj dalej."), TEXT("Ups..."), NULL);
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
