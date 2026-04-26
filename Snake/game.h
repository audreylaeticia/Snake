#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "food.h"
#include "Snake.h"

class Game
{
public:
	Game();
	void run();

private:
	sf::RenderWindow window;
	sf::Texture _textureFond;
	sf::Sprite _spriteFond;
	sf::RectangleShape _fond;
	sf::Clock clock;
	sf::Font _font;
	Snake snake;
	Food food;

	

	sf::Texture backgroundTexture;
	sf::Sprite background;
};


