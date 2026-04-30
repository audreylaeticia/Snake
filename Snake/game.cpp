#include "Snake.h"
#include "Game.h"
#include <iostream>

using namespace sf;

Game::Game()
{
    window.create(VideoMode(800, 700), "Snake");
    window.setFramerateLimit(60);

    hasStarted = false;
    gameOver = false;

    //  charger police AVANT UI
    if (!_font.loadFromFile("ressources/arial.ttf"))
    {
        std::cout << "Erreur chargement police\n";
    }

    initGameOverUI();

    // UI bar
    uiBar.setSize(sf::Vector2f(800, 100));
    uiBar.setFillColor(sf::Color(40, 40, 40));
    uiBar.setPosition(0, 0);

    // fond
    if (!_textureFond.loadFromFile("ressources/imageFond.png"))
    {
        std::cout << "Erreur chargement fond\n";
    }

    _spriteFond.setTexture(_textureFond);

    _spriteFond.setScale(
        800.0f / _textureFond.getSize().x,
        600.0f / _textureFond.getSize().y
    );

    _spriteFond.setPosition(0, 100);

    food.spawn(snake.getBody());
}

void Game::resetGame()
{
    gameOver = false;
    hasStarted = false;

    snake.initialise();
    food.spawn(snake.getBody());
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
            if (!gameOver && event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    snake.setDirection({ 0, -1 });
                    hasStarted = true;
                }

                if (event.key.code == Keyboard::Down)
                {
                    snake.setDirection({ 0, 1 });
                    hasStarted = true;
                }

                if (event.key.code == Keyboard::Left)
                {
                    snake.setDirection({ -1, 0 });
                    hasStarted = true;
                }

                if (event.key.code == Keyboard::Right)
                {
                    snake.setDirection({ 1, 0 });
                    hasStarted = true;
                }
            }

            // clic replay
            if (gameOver && event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (replayButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    resetGame();
                }
            }
        }

        //  mouvement
        if (!gameOver && hasStarted && clock.getElapsedTime().asSeconds() > 0.2f)
        {
            if (snake.willHitWall(25, 18))
            {
                gameOver = true;
            }
            else
            {
                snake.move();

                if (snake.checkSelfCollision())
                {
                    gameOver = true;
                }
            }

            clock.restart();
        }

        //  manger pomme
        if (!gameOver && snake.getHeadPosition() == food.getPosition())
        {
            snake.grow();
            food.incrementScore();
            food.spawn(snake.getBody());
        }

        // affichage
        window.clear();

        window.draw(uiBar);
        window.draw(_spriteFond);
        food.draw(window);
        snake.draw(window);

        // GAME OVER UI
        if (gameOver)
        {
            textFinalScore.setString(
                "Score: " + std::to_string(food.getScore())
            );

            window.draw(overlay);
            window.draw(panel);
            window.draw(textGameOver);
            window.draw(textFinalScore);
            window.draw(replayButton);
            window.draw(textReplay);
        }

        window.display();
    }
}

void Game::initGameOverUI()
{
    // overlay sombre
    overlay.setSize(sf::Vector2f(800, 700));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // panneau
    panel.setSize(sf::Vector2f(300, 220));
    panel.setFillColor(sf::Color(200, 160, 40));
    panel.setPosition(250, 200);

    // bouton replay
    replayButton.setSize(sf::Vector2f(200, 50));
    replayButton.setFillColor(sf::Color(50, 180, 50));
    replayButton.setPosition(300, 350);

    // texte GAME OVER
    textGameOver.setFont(_font);
    textGameOver.setString("GAME OVER");
    textGameOver.setCharacterSize(28);
    textGameOver.setFillColor(sf::Color::White);
    textGameOver.setPosition(300, 220);

    // score
    textFinalScore.setFont(_font);
    textFinalScore.setCharacterSize(20);
    textFinalScore.setFillColor(sf::Color::White);
    textFinalScore.setPosition(320, 270);

    // texte bouton
    textReplay.setFont(_font);
    textReplay.setString("REPLAY");
    textReplay.setCharacterSize(20);
    textReplay.setFillColor(sf::Color::White);
    textReplay.setPosition(350, 360);
}