#include "Snake.h"
#include "Game.h"
#include "menu.h"

using namespace std;

Menu::Menu()
{
    init();
}

// j'initialise le menu 
void Menu::init()
{
    _font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    if (!_backgroundTexture.loadFromFile("ressources/snakeImage.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    _backgroundSprite.setTexture(_backgroundTexture);

    _backgroundSprite.setScale(
        800.0f / _backgroundTexture.getSize().x,
        600.0f / _backgroundTexture.getSize().y
    );

    if (!menuMusic.openFromFile("ressources/music_music.wav"))
    {
        std::cout << "Erreur musique\n";
    }

    menuMusic.setLoop(true);
    menuMusic.play();

    // bouton play
    _playButton.setSize(sf::Vector2f(200, 50));
    _playButton.setPosition(300, 200);
    _playButton.setFillColor(sf::Color::Blue);

    _playText.setFont(_font);
    _playText.setString("Play");
    _playText.setCharacterSize(24);
    _playText.setPosition(350, 210);

    // bouton quitter
    _quitButton.setSize(sf::Vector2f(200, 50));
    _quitButton.setPosition(300, 300);
    _quitButton.setFillColor(sf::Color::Blue);

    _quitText.setFont(_font);
    _quitText.setString("Quit");
    _quitText.setCharacterSize(24);
    _quitText.setPosition(350, 310);

    // bouton infos
    _infoButton.setSize(sf::Vector2f(200, 50));
    _infoButton.setPosition(300, 400);
    _infoButton.setFillColor(sf::Color::Blue);

    _infoText.setFont(_font);
    _infoText.setString("Infos");
    _infoText.setCharacterSize(24);
    _infoText.setPosition(350, 410);

    // texte infos (mode d'emploi)
    _infoDisplay.setFont(_font);
    _infoDisplay.setCharacterSize(20);
    _infoDisplay.setFillColor(sf::Color::White);
    _infoDisplay.setPosition(50, 100);

    _infoDisplay.setString(
        "Mode d'emploi:\n\n"
        "- Fleches pour bouger\n"
        "- Mange pour grandir\n"
        "- Evite les murs\n\n"
        "Appuie sur ESC pour revenir"
    );
}

int Menu::run(sf::RenderWindow& window)
{
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // clic souris
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    // on bloque les clics si on est dans l'écran infos
                    if (!_showInfo)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        
                        if (_playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            menuMusic.stop();
                            return 1;
                        }
                        else if (_quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            return 0;
                        }
                        else if (_infoButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            _showInfo = true;
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                _showInfo = false;
            }
        }

        // position souris
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // hover play
        if (_playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            _playButton.setFillColor(sf::Color::Green);
        else
            _playButton.setFillColor(sf::Color::Blue);

        // hover quit
        if (_quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            _quitButton.setFillColor(sf::Color::Red);
        else
            _quitButton.setFillColor(sf::Color::Blue);

        //hover infos
        if (_infoButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            _infoButton.setFillColor(sf::Color::Yellow);
        else
            _infoButton.setFillColor(sf::Color::Blue);

        // affichage
        window.clear();
        window.draw(_backgroundSprite);

        if (_showInfo)
        {
            window.draw(_infoDisplay);
        }
        else
        {
            window.draw(_playButton);
            window.draw(_playText);

            window.draw(_quitButton);
            window.draw(_quitText);

            window.draw(_infoButton);
            window.draw(_infoText);
        }

        window.display();
    }

    return 0;
}