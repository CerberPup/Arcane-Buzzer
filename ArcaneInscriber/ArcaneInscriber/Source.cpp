#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

int main() {
	sf::VideoMode t = sf::VideoMode::getDesktopMode();
	cout << t.height<<" "<<t.width;
}