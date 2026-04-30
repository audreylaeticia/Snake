#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
    class mainMenu {
    private:
        // Fenêtre du jeu
        sf::RenderWindow& window;

        // Police et textes
        sf::Font font;
        sf::Text title, playText, settingsText, quitText, statsText, aboutText, instructionsText;

        // Arrière-plan
        sf::Sprite background;
        sf::Texture backgroundTexture;
    public:
        // Constructeur : initialise le menu principal avec la fenêtre passée en paramètre
        mainMenu(sf::RenderWindow& win);



    };

