#include "Snake.h"
#include "Game.h"

using namespace sf;

Game::Game()
{
    lives = 3;
   /* window.create(VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);*/

    // charger le fond
    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    if (!font.loadFromFile("ressources/arial.ttf"))
    {
        std::cout << "Erreur chargement police\n";
    }

    // config texte
    textLives.setFont(font);
    textLives.setCharacterSize(20);
    textLives.setFillColor(sf::Color::White);
    textLives.setPosition(10, 10);

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
        if (clock.getElapsedTime().asSeconds() > 0.2f)
        {
            snake.move();
            if (snake.checkCollisionWithWall(25, 18))
            {
                lives--;

                if (lives <= 0)
                {
                    window.close(); // game over
                }
                else
                {
                    snake.initialise(); // reset position
                    food.spawn(snake.getBody());
                }
            }
            clock.restart();
        }

        if (snake.getHeadPosition() == food.getPosition())
        {
            snake.grow();
            food.incrementScore();
            food.spawn(snake.getBody());
        }
        textLives.setString("Vies: " + std::to_string(lives));

        // affichage
        window.clear();

        window.draw(_spriteFond);
        food.draw(window);   
        snake.draw(window); 
        window.draw(textLives);

        window.display();
    }
}