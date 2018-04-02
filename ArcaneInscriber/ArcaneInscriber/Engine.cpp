#include "Engine.h"
#include "Logger.h"



std::shared_ptr<sf::Texture > Engine::getTexture(std::string Name)
{
	auto wynik = Tex.find(Name);
	if (wynik == Tex.end())
	{
		return nullptr;
	}
	else {
		return wynik->second;
	}
}

void Engine::setTexture(std::string Path, std::string Name)
{
	struct stat buffer;

	if (stat(Path.c_str(), &buffer) == 0) {
		//Logger::log(__FILE__, "","");
		LOG(0,"Plik Istnieje",Path,1);
		if (Tex.find(Name) == Tex.end()) 
		{
			sf::Texture* t = new sf::Texture;
			if (!t->loadFromFile(Path)) {
				throw std::runtime_error("Nie udalo sie zaladowac textury: " + Path);
			}
			Tex.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(Name, t));
		}
		else 
		{
			//LOG(0, "Tekstura istnieje", Name, 1);
		}
	}
	else {
		throw std::invalid_argument("Plik nie istnieje \""+Path+'\"');
	}
	return;
	
	
}

Engine::Engine(int w, int h) :width(w), height(h)
{
	window.create(sf::VideoMode(w, h), "Gra",sf::Style::Fullscreen);
	window.setFramerateLimit(60);
}


Engine::~Engine()
{
}

std::map<std::string, std::shared_ptr<sf::Texture >> Engine::Tex;
sf::RenderWindow Engine::window;
Engine::State Engine::state = State::SPLASH;