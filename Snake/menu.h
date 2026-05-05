#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "food.h"
#include "Snake.h"

class Menu {
private:
    sf::Font _font;

    sf::RectangleShape _playButton;
    sf::Text _playText;

    sf::RectangleShape _quitButton;
    sf::Text _quitText;

    sf::RectangleShape _infoButton;
    sf::Text _infoText;
    sf::Text _infoDisplay;
    bool _showInfo = false;

    sf::RectangleShape _resumeButton;
    sf::Text _resumeText;

    sf::Texture _backgroundTexture;

    sf::Texture _textureFond;
    sf::Sprite _backgroundSprite;
    sf::Music menuMusic;




public:
    Menu();

    void init(); // initialise les boutons
   int run(sf::RenderWindow& window, bool showResume); // lance le menu
   void stopMusic();

    
};