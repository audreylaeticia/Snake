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

    // BACKGROUND POUR INFOS
    if (!_infoBgTexture.loadFromFile("ressources/fond.png"))
    {
        std::cout << "Erreur fond infos\n";
    }

    _infoBgSprite.setTexture(_infoBgTexture);

    _infoBgSprite.setScale(
        800.0f / _infoBgTexture.getSize().x,
        600.0f / _infoBgTexture.getSize().y
    );

    if (!menuMusic.openFromFile("ressources/music_music.wav"))
    {
        std::cout << "Erreur musique\n";
    }

    menuMusic.setLoop(true);
    menuMusic.setVolume(40);

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

    _resumeButton.setSize(sf::Vector2f(200, 50));
    _resumeButton.setPosition(300, 150);
    _resumeButton.setFillColor(sf::Color::Green);

    _resumeText.setFont(_font);
    _resumeText.setString("Resume");
    _resumeText.setCharacterSize(24);
    _resumeText.setPosition(350, 160);

    // texte infos (mode d'emploi)
    _infoDisplay.setFont(_font);
    _infoDisplay.setCharacterSize(20);
    _infoDisplay.setFillColor(sf::Color::White);
    _infoDisplay.setPosition(40, 30);

    //PANEL TRANSPARENT POUR TEXTE
    _infoPanel.setSize(sf::Vector2f(760, 580));
    _infoPanel.setPosition(20, 10);
    _infoPanel.setFillColor(sf::Color(0, 0, 0, 180));

    _infoDisplay.setString(
        "SNAKE - MODE D'EMPLOI\n\n"
        "Le jeu Snake est un jeu classique ou vous controlez un serpent qui \n"
        "se déplace sur une grille.\n\n"
        "Le but est de manger la nourriture pour faire grandir le serpent et\n"
        " augmenter votre score.\n\n"
        "COMMENT JOUER :\n"
        "- Utilisez les fleches du clavier (↑ ↓ ← →)"
        "pour déplacer le serpent\n"
        "- Chaque nourriture manger augmente votre score\n"
        "- Le serpent grandit a chaque fois que vous mangez\n\n"
        "REGLES DU JEU :\n"
        "- Ne touchez pas les murs\n"
        "- Ne vous mordez pas vous-meme\n"
        "- Plus vous mangez, plus le jeu devient difficile\n\n"
        "PAUSE :\n"
        "- Appuyez sur ESC pour mettre le jeu en pause\n"
        "- Vous pouvez reprendre depuis le menu\n\n"
        "OBJECTIF :\n"
        "Obtenez le meilleur score possible et battez votre record !"

    );
}
int Menu::run(sf::RenderWindow& window, bool showResume)
{
    while (window.isOpen())
    {
        if(menuMusic.getStatus() != sf::Music::Playing)
        {
            menuMusic.play(); // 🔥 joue seulement si pas déjà en cours
        }
        sf::Event event;

        // EVENTS UNIQUEMENT
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // ESC pour quitter infos
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                if (_showInfo)
                    _showInfo = false;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (!_showInfo)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        if (showResume && _resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            return 2;

                        else if (_playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            menuMusic.stop(); 
                            return 1;
                        }

                        else if (_quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            return 0;

                        else if (_infoButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            _showInfo = true;
                    }
                }
            }
        }

        // AFFICHAGE (EN DEHORS)
        window.clear();
        window.draw(_backgroundSprite);

        if (_showInfo)
        {
            window.draw(_infoBgSprite); // IMPORTANT
            window.draw(_infoPanel);
            window.draw(_infoDisplay);
        }
        else
        {
            if (showResume)
            {
                window.draw(_resumeButton);
                window.draw(_resumeText);
            }

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

void Menu::stopMusic()
{
    menuMusic.stop();
}
