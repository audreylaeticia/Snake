#include "Snake.h"
#include "Game.h"
#include "menu.h"

Menu::Menu()
{
		init();
	
}

//j'initialise  le menu 
void Menu::init()
{
    
        _font.loadFromFile("arial.ttf");

        // pour le  bouton play
        _playButton.setSize(sf::Vector2f(200, 50));
        _playButton.setPosition(300, 200);
        _playButton.setFillColor(sf::Color::Blue);

        _playText.setFont(_font);
        _playText.setString("Play");
        _playText.setCharacterSize(24);
        _playText.setPosition(350, 210);

        // pour le  bouton quitter
        _quitButton.setSize(sf::Vector2f(200, 50));
        _quitButton.setPosition(300, 300);
        _quitButton.setFillColor(sf::Color::Blue);

        _quitText.setFont(_font);
        _quitText.setString("Quit");
        _quitText.setCharacterSize(24);
        _quitText.setPosition(350, 310);
   
}

int Menu::run(sf::RenderWindow& window)
{
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // 🖱️ clic souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (_playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return 1; // PLAY
                    }

                    if (_quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return 0; // QUIT
                    }
                }
            }
        }

        // 🖱️ position souris
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // 🎨 hover PLAY
        if (_playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            _playButton.setFillColor(sf::Color::Red);
        else
            _playButton.setFillColor(sf::Color::Blue);

        // 🎨 hover QUIT
        if (_quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            _quitButton.setFillColor(sf::Color::Red);
        else
            _quitButton.setFillColor(sf::Color::Blue);

        // 🎨 affichage
        window.clear();
        window.draw(_playButton);
        window.draw(_playText);
        window.draw(_quitButton);
        window.draw(_quitText);
        window.display();
    }

    return 0;
}
