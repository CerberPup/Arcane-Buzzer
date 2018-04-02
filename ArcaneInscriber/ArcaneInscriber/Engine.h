#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <sys\stat.h>
class Engine
{
private:
	static std::map<std::string, std::shared_ptr<sf::Texture>> Tex;
public:
	enum State { SPLASH, MAINMENU, GAME, EXIT };
	static State state;
	const unsigned short width;
	const unsigned short height;
	static std::shared_ptr<sf::Texture> getTexture(std::string Name);
	static void setTexture(std::string Path, std::string Name);//Path,Name
	static sf::RenderWindow window;
	Engine(int w, int h);
	~Engine();
};
