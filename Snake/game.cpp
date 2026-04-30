#include "Snake.h"
#include "Game.h"

using namespace sf;

Game::Game()
{
   
   /* window.create(VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);*/

    hasStarted = false;

    // charger le fond
    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        std::cout << "Erreur chargement police\n";
    }

    

    _spriteFond.setTexture(_textureFond);

    // adapter à la fenêtre
    _spriteFond.setScale(
        800.0f / _textureFond.getSize().x,
        600.0f / _textureFond.getSize().y
    );
    food.spawn(snake.getBody());
}

void Game::run(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // clavier
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    snake.setDirection({ 0, -1 });
                    hasStarted = true; 
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    snake.setDirection({ 0, 1 });
                    hasStarted = true;
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    snake.setDirection({ -1, 0 });
                    hasStarted = true;
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    snake.setDirection({ 1, 0 });
                    hasStarted = true;
                }
            }
        }

        // mouvement automatique (avec contrôle du démarrage)
        if (hasStarted && clock.getElapsedTime().asSeconds() > 0.2f)
        {
            if (snake.willHitWall(25, 18))
            {
                window.close(); // GAME OVER
            }
            else
            {
                snake.move();
                    if (snake.checkSelfCollision())
                    {
                        window.close(); // GAME OVER
                    }
            }

            clock.restart();
        }

        // collision nourriture
        if (snake.getHeadPosition() == food.getPosition())
        {
            snake.grow();
            food.incrementScore();
            food.spawn(snake.getBody());
        }

        // affichage
        window.clear();

        window.draw(_spriteFond);
        food.draw(window);
        snake.draw(window);

        window.display();
    }
}