#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	//~Game();
	void run();

private:
	sf::RenderWindow window;
	sf::RectangleShape player;
	Snake snake;

	//enum Direction { UP, DOWN, LEFT, RIGHT };
	//Direction dir;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Clock clock;
};


