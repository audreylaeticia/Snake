#include "Game.h"

using namespace sf;

Game::Game()
{
    window.create(VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);

    // charger le fond
    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    _spriteFond.setTexture(_textureFond);

    // adapter à la fenêtre
    _spriteFond.setScale(
        800.0f / _textureFond.getSize().x,
        600.0f / _textureFond.getSize().y
    );
}

void Game::run()
{
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // clavier
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                    snake.setDirection({ 0, -1 });

                if (event.key.code == Keyboard::Down)
                    snake.setDirection({ 0, 1 });

                if (event.key.code == Keyboard::Left)
                    snake.setDirection({ -1, 0 });

                if (event.key.code == Keyboard::Right)
                    snake.setDirection({ 1, 0 });
            }
        }

        // mouvement automatique
        if (clock.getElapsedTime().asMilliseconds() > 150)
        {
            snake.move();
            clock.restart();
        }

        // affichage
        window.clear();

        window.draw(_spriteFond); // fond
        snake.draw(window);       // serpent

        window.display();
    }
}