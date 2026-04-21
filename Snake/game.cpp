#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Game.h"

//using namespaces std;

Game::Game()
{
    window.create(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond" << std::endl;
    }

    background.setTexture(backgroundTexture);

    
    background.setScale(
        800.0f / backgroundTexture.getSize().x,
        600.0f / backgroundTexture.getSize().y
    );

}
void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    snake.setDirection(0);

                if (event.key.code == sf::Keyboard::Down)
                    snake.setDirection(1);

                if (event.key.code == sf::Keyboard::Left)
                    snake.setDirection(2);

                if (event.key.code == sf::Keyboard::Right)
                    snake.setDirection(3);
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 150)
        {
            snake.move();
            clock.restart();
        }

        window.clear();
        window.draw(background);
        snake.draw(window);
        window.display();
    }
}