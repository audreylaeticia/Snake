#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "food.h"
#include "Snake.h"
#include "menu.h"

class Game
{
public:
	Game();
	void run();
	void initGameOverUI();
	void resetGame();
	void startMusic();

private:
	sf::RenderWindow window;
	sf::Texture _textureFond;
	sf::Sprite _spriteFond;
	sf::RectangleShape _fond;
	sf::Clock clock;
	sf::Font _font;
	sf::RectangleShape uiBar;

	sf::Texture backgroundTexture;
	sf::Sprite background;
	

	sf::RectangleShape overlay;
	sf::RectangleShape panel;
	sf::RectangleShape replayButton;

	sf::Text textGameOver;
	sf::Text textFinalScore;
	sf::Text textReplay;
	Snake snake;
	Food food;
	sf::SoundBuffer keyBuffer;
	sf::Sound keySound;

	sf::SoundBuffer eatBuffer;
	sf::Sound eatSound;
	sf::Music gameMusic;

	bool hasStarted;
	bool gameOver;

	float speed;
	float minSpeed;
	

};


